

cplusplus {{
    #include "openflow.h"
    #include "Open_Flow_Message_m.h"
}};


packet Open_Flow_Message;



packet OFP_Stats_Request extends Open_Flow_Message
{
    uint16_t type;  //* One of the OFPMP_* constants. */
	uint16_t flags; //* OFPMPF_REPLY_* flags. */
	uint8_t pad[4];
	uint8_t body[]; //* Body of the reply. */
}