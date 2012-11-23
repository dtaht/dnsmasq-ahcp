struct prefix_list *our_ipv6_address;

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

extern struct config_data *config_data;

