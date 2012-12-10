struct prefix_list *our_ipv6_address;

/* from the original code */
/* This is used both to hold the contents of a message and to hold our
   current configuration. */

struct config_data {
    /* The following fields come from a message */
    unsigned origin, origin_m, expires, expires_m;
    struct prefix_list *server_ipv6, *server_ipv4;
    struct prefix_list *ipv6_prefix, *ipv4_prefix,
        *ipv6_address, *ipv4_address,
        *ipv6_prefix_delegation, *ipv4_prefix_delegation;
    int ipv4_mandatory, ipv6_mandatory,
        ipv4_delegation_mandatory, ipv6_delegation_mandatory;
    struct prefix_list *name_server, *ntp_server;
};

/* then I started rethinking things */

extern struct config_data *config_data;

struct prefix {
	inaddr_6 addr;
	int prefix;
};

enum mandatory_options {
	AHCP_MANDATORY_NONE=0,
	AHCP_MANDATORY_IPV6=1,
	AHCP_MANDATORY_IPV4=2,
	AHCP_MANDATORY_IPV6_DELEGATION=4,
	AHCP_MANDATORY_IPV4_DELEGATION=8,
};

/* Rather than use lists, just hard code a reasonable value.
   Use conventional 6 encodings for ipv4 
   The default value of 16 is 14 more than is usually needed 

   After thinking about this format for a while, I'm thinking
   about using malloc again... */

#define AHCP_SERVERS 16

struct ahcp_config {
    /* The following fields come from a message */
    enum mandatory mandatory_options;
    unsigned origin, origin_m, expires, expires_m;
    struct prefix servers[AHCP_SERVERS];
    struct prefix prefixes[AHCP_SERVERS];
    struct prefix name_servers[AHCP_SERVERS]; 
    struct prefix ntp_servers[AHCP_SERVERS];
};

struct ahcp_packet_t {
    enum mandatory mandatory_options;
    unsigned origin, origin_m, expires, expires_m;
    struct prefix servers[AHCP_SERVERS];
    struct prefix prefixes[AHCP_SERVERS];
    struct prefix name_servers[AHCP_SERVERS]; 
    struct prefix ntp_servers[AHCP_SERVERS];
};
