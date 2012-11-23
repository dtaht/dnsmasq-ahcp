/* dnsmasq is Copyright (c) 2000-2012 Simon Kelley

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 dated June, 1991, or
   (at your option) version 3 dated 29 June, 2007.
 
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
     
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#define AHCP_ALL_SERVERS	"ff02::cca6:c0f9:e182:5359"
#define AHCP_SERVER_PORT	5359

#define AHCP_DISCOVER		0
#define AHCP_OFFER		1
#define AHCP_REQUEST		2
#define AHCP_ACK		3
#define AHCP_NACK		4
#define AHCP_RELEASE		5

/* TLVS */

#define AHCP_MANDATORY		1
#define AHCP_ORIGINTIME		2
#define AHCP_EXPIRES		3
#define AHCP_MY_IPV6_ADDRESS	4
#define AHCP_MY_IPV4_ADDRESS	5
#define AHCP_IPV6_PREFIX	6
#define AHCP_IPV4_PREFIX	7
#define AHCP_IPV6_ADDRESS	8
#define AHCP_IPV4_ADDRESS	9
#define AHCP_IPV6_PD		10
#define AHCP_IPV4_PD		11
#define AHCP_IPV6_NAMESERVER	12
#define AHCP_IPV6_NTPSERVER	13

/* non standard Extensions */

#define AHCP_IPV6_DOMAIN	20
#define AHCP_IPV6_NAME		21
#define AHCP_IPV6_PROTOCOL	22
#define AHCP_GW			23

/* Error Codes */

#define ACHPSUCCESS     0
#define AHCPUNSPEC      1
#define AHCPNOADDRS     2
#define AHCPNOBINDING   3
#define AHCPNOTONLINK   4
#define AHCPUSEMULTI    5

