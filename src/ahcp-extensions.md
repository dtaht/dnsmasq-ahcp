* Routing Protocol Extension
  When not present the default routing protocol is babel, for
  backward compatability.

  When present the TLV can have any of several states.
  A length of 0 indicates that the requesting host has no innate
  ability to route and a static route and default gw MUST be 
  provided.
  
  An ascii character string, containing the name of the desirable
  routing protocol, not null terminated. Values that can be 
  supplied are: "none", "babel", "ospfv3", "batman",
  with more to be user defined.
  
  Multiple instances of this TLV can be provided, with routing
  protocols the client can interact with supported. This includes
  "none", however "none" should be the least desirable option.

0                   1                   2                   3
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|  Option no. |     Length      |string...|

* Default gateway
  When "none" is chosen by the server, or an empty routing protocol
  is selected, a default gateway MUST be provided by the server 
  to the client. 

* Requested Name
  A client may optionally supply a proposed name to the AHCP server.

* Assigned name
  A server may optionally supply a proposed name to the AHCP client.
  This name MUST be registered in the AHCP server's primary DNS.

