static int parse_request(packet p, int req) {
	switch(request) {
		case AHCP_DISCOVER:
		case AHCP_OFFER:
		case AHCP_REQUEST:
		case AHCP_ACK:
		case AHCP_NACK:
		case AHCP_RELEASE:
		case default: printf("AHCP packet type %d received\n": request);
	}
	return 0;
}

/* Parse TLVS */

static int parse_tlv(packet p, int tlv) {
	switch(tlv) {
	case ACHP_MANDATORY:
	case AHCP_ORIGINTIME:
	case AHCP_EXPIRES:
	case AHCP_MY_IPV6_ADDRESS:
	case AHCP_MY_IPV4_ADDRESS:
	case AHCP_IPV6_PREFIX:
	case AHCP_IPV4_PREFIX:
	case AHCP_IPV6_ADDRESS:
	case AHCP_IPV4_ADDRESS:
	case AHCP_IPV6_PD:
	case AHCP_IPV4_PD:
	case AHCP_IPV6_NAMESERVER:
	case AHCP_IPV6_NTPSERVER:
#ifdef AHCP_EXTENSIONS
	case AHCP_IPV6_DOMAIN:
	case AHCP_IPV6_NAME:
	case AHCP_IPV6_PROTOCOL:
	case AHCP_GW:
#endif
	case default: printf("ahcp tlv %d received\n",tlv);
	}
	return 0;
}

/*
ACHPSUCCESS
AHCPUNSPEC
AHCPNOADDRS
AHCPNOBINDING
AHCPNOTONLINK
AHCPUSEMULTI
*/
