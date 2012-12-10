/* ths just pulls some needed functions from the existing ahcpd code
   and extracts the server specific portions, so they can be clearly
   seen and has some comments as to where to go next

   my intent was to rewrite it all to eliminate most (all?) uses of
   malloc in the code...

I will have to insert the original copyright message here 

*/

unsigned
roughly(unsigned value)
{
    return value * 3 / 4 + random() % (value / 4);
}

// Stub this out for now

int release_lease(void *a,void *b, void *c) {
  return 0;
}

/* Unclear if this needs to get called in dnsmasq */

unique_id() {
  int fd;
  struct timeval now;
  gettime(&now, NULL);

  fd = open("/dev/urandom", O_RDONLY);
  if(fd < 0) {
    struct timeval tv;
    perror("open(random)");
    get_real_time(&tv, NULL);
    seed = tv.tv_sec ^ tv.tv_usec;
  } else {
    rc = read(fd, &seed, sizeof(unsigned int));
    if(rc < sizeof(unsigned int)) {
      perror("read(random)");
      goto fail;
    }
    close(fd);
  }
  srandom(seed);

  myseqno = random();

  if(unique_id_file && unique_id_file[0] != '\0') {
    fd = open(unique_id_file, O_RDONLY);
    if(fd >= 0) {
      rc = read(fd, myid, 8);
      if(rc == 8) {
	close(fd);
	goto unique_id_done;
      }
      close(fd);
    }
  }

  for(i = 0; i < numnetworks; i++) {
    rc = if_eui64(interfaces[i], myid);
    if(rc >= 0)
      goto write_unique_id;
  }
  
  rc = random_eui64(myid);
  if(rc < 0) {
    fprintf(stderr, "Couldn't generate unique id.\n");
    goto fail;
  }

 write_unique_id:
  if(unique_id_file && unique_id_file[0] != '\0') {
    fd = open(unique_id_file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
    if(fd < 0) {
      perror("creat(unique_id)");
        } else {
      rc = write(fd, myid, 8);
      if(rc != 8) {
	perror("write(unique_id)");
	unlink(unique_id_file);
      }
      close(fd);
    }
  }
  
 unique_id_done:
}
  

ahcp_process_msg(config *c,packet *body) {
  if(server_config) {
    switch(body[0]) { 
    AHCP_DISCOVER:
    AHCP_REQUEST:
    AHCP_RELEASE: {
	struct config_data *config;
	unsigned client_lease_time;
	unsigned char reply[BUFFER_SIZE];
	int hopcount;
	unsigned char ipv4[4] = {0};
    
	config = parse_message(-1, body, bodylen, interfaces);
	if(!config) {
	  fprintf(stderr, "Unparseable client message.\n");
	  continue;
	}
	
	hopcount = buf[3];
	if(config->ipv4_address)
	  prefix_list_extract4(ipv4, config->ipv4_address);
	client_lease_time =
	  config->expires ?
	  config->expires + roughly(120) :
	  4 * 3600 + roughly(120);
	
	free_config_data(config);
    
	if(body[0] == AHCP_RELEASE) {
	  if(memcmp(ipv4, zeroes, 4) != 0) {
	    rc = release_lease(buf + 8, 8, ipv4);
	    if(rc < 0) {
	      char a[INET_ADDRSTRLEN];
	      inet_ntop(AF_INET, ipv4, a,
			INET_ADDRSTRLEN);
	      fprintf(stderr,
		      "Couldn't release lease for %s.\n",
		      a);
	    }
	   }
	  continue;
	}
    
    if((config->ipv4_mandatory &&
	!server_config->lease_first[0]) ||
       (config->ipv6_mandatory &&
	!server_config->ipv6_prefix) ||
       config->ipv4_delegation_mandatory ||
       config->ipv6_delegation_mandatory) {
      /* We won't be able to satisfy the client's
	 mandatory constraints. */
      rc = -1;
    } else if(server_config->lease_first[0] &&
	      config->ipv4_address) {
      rc = take_lease(buf + 8, 8,
		      memcmp(ipv4, zeroes, 4) == 0 ?
		      ipv4 : NULL,
		      ipv4, &client_lease_time,
		      body[0] == AHCP_REQUEST);
    } else {
      rc = 0;
    }
    
    /* If the client is in the initial state, there's
       no point in notifying it about failures -- it
       will time out and fall back to another server */
    if(rc < 0 && body[0] == AHCP_DISCOVER)
      continue;
    
    config =
      make_config_data(client_lease_time,
		       ipv4, server_config,
		       interfaces);
    if(config == NULL) {
      fprintf(stderr, "Couldn't build config data.\n");
      continue;
    }
    
    rc = server_body(rc < 0 ? AHCP_NACK :
		     body[0] == AHCP_DISCOVER ?
		     AHCP_OFFER : AHCP_ACK,
		     config, reply, BUFFER_SIZE);
    if(rc < 0) {
      fprintf(stderr, "Couldn't build reply.\n");
    } else {
      debugf(2, "Sending %d (%d bytes, %d hops).\n",
	     reply[0], rc, hopcount);
      //      usleep(roughly(50000));
      send_packet(psin, sinlen, buf + 8, hopcount,
		  reply, rc);
      gettime(&now, NULL);
    }
    
    free_config_data(config);
    
  }
 }
