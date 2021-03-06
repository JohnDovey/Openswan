#define INCLUDE_IKEV1_PROCESSING
#define INCLUDE_QUICK_MODE
#define OMIT_SEAM_INITIATE
#define OMIT_MAIN_MODE
#define OMIT_IKEv1
#define OMIT_ADD_PENDING
#define OMIT_PENDING_USE
#define NAPT_ENABLED 1
#define NAT_TRAVERSAL
#define SEAM_CRYPTO
#define FIREWALL_OUTSIDE "192.168.0.1"
#include "../lp10-parentI2/parentI2_head.c"
#include "seam_host_alice.c"
#include "seam_kernel.c"
#include "nat_traversal.h"
#include "seam_rsasig.c"
#include "seam_x509.c"
#include "seam_dpd.c"
#include "seam_command.c"
#include "seam_ikev1_crypto.c"
#include "seam_nonce.c"
#include "seam_rsa_check.c"
#include "seam_gi_3des_md5.c"
#include "seam_sendI1.c"
#include "seam_finish.c"
#include "seam_ikev1_aggr.c"

#define TESTNAME "v1rwnatQI1"

bool no_cr_send = 0;

static void init_local_interface(void)
{
    nat_traversal_support_non_ike = TRUE;
    nat_traversal_support_port_floating = TRUE;
    nat_traversal_enabled = TRUE;
    init_alice_interface(TRUE);
}

static void init_fake_secrets(void)
{
    prompt_pass_t pass;
    memset(&pass, 0, sizeof(pass));

    osw_init_ipsecdir(SAMPLEDIR "alice");
    osw_load_preshared_secrets(&pluto_secrets
			       , TRUE
			       , SAMPLEDIR "alice.secrets"
			       , &pass, NULL);
}

static void init_loaded(void) {}

#include "seam_ikev1tc3.c"

#ifndef PCAP_INPUT_COUNT
#define PCAP_INPUT_COUNT 3
recv_pcap recv_inputs[PCAP_INPUT_COUNT]={
    recv_pcap_packet,
    recv_pcap_packet2ikev1,
    recv_pcap_packet3ikev1,
};
#endif

#include "../lp10-parentI2/parentI2_main.c"

 /*
 * Local Variables:
 * c-style: pluto
 * c-basic-offset: 4
 * compile-command: "make check"
 * End:
 */
