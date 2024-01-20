/* -*-  mode:c; tab-width:8; c-basic-offset:8; indent-tabs-mode:nil;  -*- */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "libsmb2.h"
#include "smb2.h"
#include "../lib/ntlmssp.h"

time_t timestamp = 1559429385;

unsigned char security_blob[] = {
    0x4e, 0x54, 0x4c, 0x4d, 0x53, 0x53, 0x50, 0x00,
    0x02, 0x00, 0x00, 0x00, 0x08, 0x00, 0x08, 0x00,
    0x38, 0x00, 0x00, 0x00, 0x05, 0x02, 0x8a, 0xa2,
    0x02, 0x2b, 0xb9, 0x85, 0x51, 0xa1, 0x4a, 0xca,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x3a, 0x00, 0x3a, 0x00, 0x40, 0x00, 0x00, 0x00,
    0x06, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f,
    0x58, 0x00, 0x42, 0x00, 0x4d, 0x00, 0x43, 0x00,
    0x02, 0x00, 0x08, 0x00, 0x58, 0x00, 0x42, 0x00,
    0x4d, 0x00, 0x43, 0x00, 0x01, 0x00, 0x08, 0x00,
    0x58, 0x00, 0x42, 0x00, 0x4d, 0x00, 0x43, 0x00,
    0x04, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00,
    0x08, 0x00, 0x78, 0x00, 0x62, 0x00, 0x6d, 0x00,
    0x63, 0x00, 0x07, 0x00, 0x08, 0x00, 0x36, 0x78,
    0xf0, 0x50, 0xc1, 0x18, 0xd5, 0x01, 0x00, 0x00,
    0x00, 0x00};

char client_challenge[8] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };

unsigned char expected_blob[] = {
0x4e, 0x54, 0x4c, 0x4d, 0x53, 0x53, 0x50, 0x00,
0x03, 0x00, 0x00, 0x00, 0x18, 0x00, 0x18, 0x00, 
0x72, 0x00, 0x00, 0x00, 0x6a, 0x00, 0x6a, 0x00, 
0x8a, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x0c, 0x00, 
0x40, 0x00, 0x00, 0x00, 0x10, 0x00, 0x10, 0x00, 
0x4c, 0x00, 0x00, 0x00, 0x16, 0x00, 0x16, 0x00, 
0x5c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x07, 0x02, 0x08, 0xa0, 
0x44, 0x00, 0x6f, 0x00, 0x6d, 0x00, 0x61, 0x00, 
0x69, 0x00, 0x6e, 0x00, 0x55, 0x00, 0x73, 0x00, 
0x65, 0x00, 0x72, 0x00, 0x6e, 0x00, 0x61, 0x00, 
0x6d, 0x00, 0x65, 0x00, 0x57, 0x00, 0x6f, 0x00, 
0x72, 0x00, 0x6b, 0x00, 0x73, 0x00, 0x74, 0x00, 
0x61, 0x00, 0x74, 0x00, 0x69, 0x00, 0x6f, 0x00, 
0x6e, 0x00, 0x23, 0x62, 0x8c, 0xb8, 0x79, 0xfb, 
0x73, 0x3f, 0x9a, 0x20, 0xc7, 0xaa, 0xb8, 0x17, 
0xbc, 0x45, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 
0x07, 0x08, 0x96, 0x1b, 0xfb, 0x56, 0x51, 0x7c, 
0xdb, 0x5b, 0x52, 0x62, 0x64, 0x92, 0x81, 0xf3, 
0x01, 0x7e, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x80, 0x4a, 0xb2, 0x4e, 0xcc, 0x18, 
0xd5, 0x01, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 
0x07, 0x08, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 
0x08, 0x00, 0x58, 0x00, 0x42, 0x00, 0x4d, 0x00, 
0x43, 0x00, 0x01, 0x00, 0x08, 0x00, 0x58, 0x00, 
0x42, 0x00, 0x4d, 0x00, 0x43, 0x00, 0x04, 0x00, 
0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x08, 0x00, 
0x78, 0x00, 0x62, 0x00, 0x6d, 0x00, 0x63, 0x00, 
0x07, 0x00, 0x08, 0x00, 0x36, 0x78, 0xf0, 0x50, 
0xc1, 0x18, 0xd5, 0x01, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00};

int main(int argc, char *argv[])
{
        struct smb2_session_setup_request req;
	struct smb2_context *smb2;
        void *auth_data;
        int i;

	smb2 = smb2_init_context();
        if (smb2 == NULL) {
                fprintf(stderr, "Failed to init context\n");
                return -1;
        }
	
	printf("size of security blob:%d\n", sizeof(security_blob));

        /* Session setup request. */
        memset(&req, 0, sizeof(struct smb2_session_setup_request));
        req.security_mode = SMB2_NEGOTIATE_SIGNING_ENABLED;

        auth_data = ntlmssp_init_context("Username",
                                         "Password",
                                         "Domain",
                                         "Workstation",
                                         client_challenge);
        if (auth_data == NULL) {
                smb2_destroy_context(smb2);
                fprintf(stderr, "Failed to init auth_data\n");
                return -1;
        }
                
        if (ntlmssp_generate_blob(smb2, timestamp, auth_data,
                                  security_blob, sizeof(security_blob),
                                  &req.security_buffer,
                                  &req.security_buffer_length) < 0) {
                smb2_destroy_context(smb2);
                return -1;
        }

        printf("Size of generated blob: %d\n", req.security_buffer_length);
        for (i = 0; i < req.security_buffer_length; i++) {
                printf("0x%02x ", req.security_buffer[i]);
                if (i%8 == 7) {
                        printf("\n");
                }
        }
        printf("\n");

        if (memcmp(req.security_buffer, expected_blob, sizeof(expected_blob))) {
                smb2_destroy_context(smb2);
                fprintf(stderr, "Generated blob does not match expected blob\n");
                return -1;
        }

        smb2_destroy_context(smb2);
	return 0;
}
