#include <stdio.h>
#include <stdlib.h>
#include <libnet.h>
#include <stdint.h>

int main() {

  libnet_t *l;  /* the libnet context */
  char errbuf[LIBNET_ERRBUF_SIZE], target_ip_addr_str[16];
  u_int32_t target_ip_addr, src_ip_addr;
  u_int8_t mac_broadcast_addr[6] = {0xff, 0xff, 0xff, 0xff,\
          0xff, 0xff},
     mac_zero_addr[6] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
  struct libnet_ether_addr *src_mac_addr;
  int bytes_written;

  char dev[]={"lo"};

  l = libnet_init(LIBNET_RAW4, dev, errbuf);
  if ( l == NULL ) {
    fprintf(stderr, "libnet_init() failed: %s\n", errbuf);
    exit(EXIT_FAILURE);
  }

  /* Getting our own MAC and IP addresses */

  src_ip_addr = libnet_get_ipaddr4(l); // get our ip address
  if ( src_ip_addr == -1 ) {
    fprintf(stderr, "Couldn't get own IP address: %s\n",\
                    libnet_geterror(l));
    libnet_destroy(l);
    exit(EXIT_FAILURE);
  }

  src_mac_addr = libnet_get_hwaddr(l); // get our mac address
  if ( src_mac_addr == NULL ) {
    fprintf(stderr, "Couldn't get own IP address: %s\n",\
                    libnet_geterror(l));
    libnet_destroy(l);
    exit(EXIT_FAILURE);
  }

  /* Getting target IP address */

  printf("Target IP address: ");
  scanf("%15s",target_ip_addr_str);

  target_ip_addr = libnet_name2addr4(l, target_ip_addr_str,\
      LIBNET_DONT_RESOLVE); // convert from sting format to 16 bit

  if ( target_ip_addr == -1 ) {
    fprintf(stderr, "Error converting IP address.\n");
    libnet_destroy(l);
    exit(EXIT_FAILURE);
  }

  /* Building ARP header 

  if ( libnet_autobuild_arp (ARPOP_REQUEST,\
      src_mac_addr->ether_addr_octet,\
      (u_int8_t*)(&src_ip_addr), mac_zero_addr,\
      (u_int8_t*)(&target_ip_addr), l) == -1)
  {
    fprintf(stderr, "Error building ARP header: %s\n",\
        libnet_geterror(l));
    libnet_destroy(l);
    exit(EXIT_FAILURE);
  } */

  /* build udp header*/
  struct libnet_udp_hdr udp_hdr;
     /*libnet_ptag_t libnet_build_udp (u_int16_t sp, u_int16_t dp, u_int16_t len,
       u_int16_t sum, u_int8_t * payload, u_int32_t payload_s, libnet_t * l,
       libnet_ptag_t ptag)*/
  u_int16_t sp= htons(2500); // source port
  u_int16_t dp= htons(2600); // destination port
  if(libnet_build_udp (sp, dp, LIBNET_UDP_H, 0, NULL, 0, l,0)==-1)
  {
    fprintf(stderr, "Error building UDP header: %s\n",\
        libnet_geterror(l));
    libnet_destroy(l);
    exit(EXIT_FAILURE);
  };
  /*

  /*libnet_ptag_t libnet_build_ipv4 (u_int16_t len,
    u_int8_t tos, u_int16_t id, u_int16_t frag,
    u_int8_t ttl, u_int8_t prot, u_int16_t sum,
    u_int32_t src, u_int32_t dst, u_int8_t * payload,
    u_int32_t payload_s, libnet_t * l, libnet_ptag_t ptag)*/


   if ( libnet_build_ipv4((LIBNET_IPV4_H +
          LIBNET_UDP_H ), 0,
        0, 0, 255, IPPROTO_UDP, 0, src_ip_addr,
        target_ip_addr, NULL, 0, l, 0) == -1 )
  {
    fprintf(stderr, "Error building IP header: %s\n",\
        libnet_geterror(l));
    libnet_destroy(l);
    exit(EXIT_FAILURE);
  }

  /* Building Ethernet header */

  /*if ( libnet_autobuild_ethernet (mac_broadcast_addr,\
                          ETHERTYPE_ARP, l) == -1 )
  {
    fprintf(stderr, "Error building Ethernet header: %s\n",\
        libnet_geterror(l));
    libnet_destroy(l);
    exit(EXIT_FAILURE);
  }*/

  /* Writing packet */

  bytes_written = libnet_write(l);
  if ( bytes_written != -1 )
    printf("%d bytes written.\n", bytes_written);
  else
    fprintf(stderr, "Error writing packet: %s\n",\
        libnet_geterror(l));

  libnet_destroy(l);
  return 0;
}