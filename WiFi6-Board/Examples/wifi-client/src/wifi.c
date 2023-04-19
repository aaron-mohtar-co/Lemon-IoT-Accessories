/*
 * Copyright (c) 2023 Craig Peacock.
 * Copyright (c) 2017 ARM Ltd.
 * Copyright (c) 2016 Intel Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/net/net_if.h>
#include <zephyr/net/wifi_mgmt.h>
#include <zephyr/net/net_event.h>
#include <zephyr/net/net_if.h>
#include <zephyr/net/ethernet.h>
#include <zephyr/net/ethernet_mgmt.h>
#include <errno.h>
#include "http_get.h"

/*
 * Set your access point name and paraphase below:
 */

#define SSID "test_ap"
#define PSK "secretsquirrel"

/*
 * Assign locally administered MAC address if not set in OTP
 * Four ranges exist:
 *  x2-xx-xx-xx-xx-xx, x6-xx-xx-xx-xx-xx, xA-xx-xx-xx-xx-xx, xE-xx-xx-xx-xx-xx
 */
#define MAC_ADDRESS 0x02, 0x00, 0x00, 0x00, 0x00, 0x01

static K_SEM_DEFINE(wifi_connected, 0, 1);
static K_SEM_DEFINE(ipv4_address_obtained, 0, 1);

static struct net_mgmt_event_callback wifi_cb;
static struct net_mgmt_event_callback ipv4_cb;

static void handle_wifi_connect_result(struct net_mgmt_event_callback *cb)
{
    const struct wifi_status *status = (const struct wifi_status *)cb->info;

    if (status->status)
    {
        printk("Connection request failed (%d)\n", status->status);
    }
    else
    {
        printk("Connected\n");
        k_sem_give(&wifi_connected);
    }
}

static void handle_wifi_disconnect_result(struct net_mgmt_event_callback *cb)
{
    const struct wifi_status *status = (const struct wifi_status *)cb->info;

    if (status->status)
    {
        printk("Disconnection request (%d)\n", status->status);
    }
    else
    {
        printk("Disconnected\n");
        k_sem_take(&wifi_connected, K_NO_WAIT);
    }
}

static void handle_ipv4_result(struct net_if *iface)
{
    int i = 0;

    for (i = 0; i < NET_IF_MAX_IPV4_ADDR; i++) {

        char buf[NET_IPV4_ADDR_LEN];

        if (iface->config.ip.ipv4->unicast[i].addr_type != NET_ADDR_DHCP) {
            continue;
        }

        printk("IPv4 address: %s\n",
                net_addr_ntop(AF_INET,
                                &iface->config.ip.ipv4->unicast[i].address.in_addr,
                                buf, sizeof(buf)));
        printk("Subnet: %s\n",
                net_addr_ntop(AF_INET,
                                &iface->config.ip.ipv4->netmask,
                                buf, sizeof(buf)));
        printk("Router: %s\n",
                net_addr_ntop(AF_INET,
                                &iface->config.ip.ipv4->gw,
                                buf, sizeof(buf)));
        }

        k_sem_give(&ipv4_address_obtained);
}

static void wifi_mgmt_event_handler(struct net_mgmt_event_callback *cb, uint32_t mgmt_event, struct net_if *iface)
{
    switch (mgmt_event)
    {

        case NET_EVENT_WIFI_CONNECT_RESULT:
            handle_wifi_connect_result(cb);
            break;

        case NET_EVENT_WIFI_DISCONNECT_RESULT:
            handle_wifi_disconnect_result(cb);
            break;

        case NET_EVENT_IPV4_ADDR_ADD:
            handle_ipv4_result(iface);
            break;

        default:
            break;
    }
}

void wifi_connect(void)
{
    struct net_if *iface = net_if_get_default();

    struct wifi_connect_req_params wifi_params = {0};

    wifi_params.ssid = SSID;
    wifi_params.psk = PSK;
    wifi_params.ssid_length = strlen(SSID);
    wifi_params.psk_length = strlen(PSK);
    wifi_params.channel = WIFI_CHANNEL_ANY;
    wifi_params.security = WIFI_SECURITY_TYPE_PSK;
    wifi_params.band = WIFI_FREQ_BAND_2_4_GHZ; 
    wifi_params.mfp = WIFI_MFP_OPTIONAL;

    printk("Connecting to SSID: %s\n", wifi_params.ssid);

    if (net_mgmt(NET_REQUEST_WIFI_CONNECT, iface, &wifi_params, sizeof(struct wifi_connect_req_params)))
    {
        printk("WiFi Connection Request Failed\n");
    }
}

void wifi_status(void)
{
    struct net_if *iface = net_if_get_default();
    
    struct wifi_iface_status status = {0};

    if (net_mgmt(NET_REQUEST_WIFI_IFACE_STATUS, iface, &status,	sizeof(struct wifi_iface_status)))
    {
        printk("WiFi Status Request Failed\n");
    }

    printk("\n");

    if (status.state >= WIFI_STATE_ASSOCIATED) {
        printk("SSID: %-32s\n", status.ssid);
        printk("Band: %s\n", wifi_band_txt(status.band));
        printk("Channel: %d\n", status.channel);
        printk("Security: %s\n", wifi_security_txt(status.security));
        printk("RSSI: %d\n", status.rssi);
    }
}

void wifi_disconnect(void)
{
    struct net_if *iface = net_if_get_default();

    if (net_mgmt(NET_REQUEST_WIFI_DISCONNECT, iface, NULL, 0))
    {
        printk("WiFi Disconnection Request Failed\n");
    }
}

void wifi_interface_setup()
{
    /*
     * New nRF7002's come with the OTP memory blank. i.e. no programmed MAC Address.
     * It will report:
     * <inf> wifi_nrf: wifi_nrf_fmac_otp_mac_addr_get:  Invalid OTP MAC addr: 000000000000
     * <err> wifi_nrf: wifi_nrf_if_start_zep: Invalid MAC address: 00:00:00:00:00:00
     * and the wlan0 interface will not be up.
     * 
     * We set the MAC address and bring the interface up
     */

    int ret;
    struct net_if *iface = net_if_get_default();
    struct net_linkaddr *linkaddr = net_if_get_link_addr(iface);
    struct ethernet_req_params params = {0};
    bool mac_non_zero = false;

    printk("Hostname: %s\r\n", net_hostname_get());

    if (linkaddr->type == NET_LINK_ETHERNET)
    {
        printk("Ethernet MAC Address = ");
        for (int i = 0; i < linkaddr->len; i++) {
            printk("%02X",linkaddr->addr[i]);
            if (i < (linkaddr->len -1)) printk(":");
            if (linkaddr->addr[i] != 0x00) mac_non_zero = true;
        }
        printk("\r\n");
    }

    if (net_if_is_up(iface)) {
        printk("Network Interface %s is up.\r\n", iface->if_dev->dev->name);
    } else {
        printk("Network Interface %s is down.\r\n", iface->if_dev->dev->name);
    }

    if (!mac_non_zero) {
        printk("Setting MAC Address\r\n");

        int8_t mac_id_string[6] = {MAC_ADDRESS};
        memcpy(params.mac_address.addr, mac_id_string, 6);

        ret = net_mgmt(NET_REQUEST_ETHERNET_SET_MAC_ADDRESS, iface, &params, sizeof(struct ethernet_req_params));
        if (ret != 0)
        {
            printk("Eth Set MAC Address Request Failed (%d)\n",ret);
        }

        if (net_if_up(iface) == 0) {
            printk("Network Interface %s is up.\r\n", iface->if_dev->dev->name);
        } else {
            printk("Unable to bring up %s interface\n", iface->if_dev->dev->name);
        }

        k_sleep(K_SECONDS(1));
    }
}

void main(void)
{
    int sock;

    printk("WiFi Example\nBoard: %s\n", CONFIG_BOARD);

    net_mgmt_init_event_callback(&wifi_cb, wifi_mgmt_event_handler,
                                 NET_EVENT_WIFI_CONNECT_RESULT | NET_EVENT_WIFI_DISCONNECT_RESULT);

    net_mgmt_init_event_callback(&ipv4_cb, wifi_mgmt_event_handler, NET_EVENT_IPV4_ADDR_ADD);

    net_mgmt_add_event_callback(&wifi_cb);
    net_mgmt_add_event_callback(&ipv4_cb);

    // Delay to prevent "Unable to get wpa_s handle for wlan0" on nRF Connect SDK 2.3.0.?
    printk("Sleeping for 1 second while wlan0 comes up\n");
    k_sleep(K_SECONDS(1));

    wifi_interface_setup();
    wifi_connect();
    k_sem_take(&wifi_connected, K_FOREVER);
    wifi_status();
    k_sem_take(&ipv4_address_obtained, K_FOREVER);
    printk("Ready...\n\n");
    
    printk("Looking up IP addresses:\n");
    struct zsock_addrinfo *res;
    nslookup("iot.beyondlogic.org", &res);
    print_addrinfo_results(&res);

    printk("Connecting to HTTP Server:\n");
    sock = connect_socket(&res);
    http_get(sock, "iot.beyondlogic.org", "/test.txt");
    zsock_close(sock);
    
    // Stay connected for 30 seconds, then disconnect.
    //k_sleep(K_SECONDS(30));    
    //wifi_disconnect();
}
