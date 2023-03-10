/*

mpaux.h

Author: Tatu Ylonen <ylo@cs.hut.fi>

Copyright (c) 1995 Tatu Ylonen <ylo@cs.hut.fi>, Espoo, Finland
                   All rights reserved

Created: Sun Jul 16 04:29:30 1995 ylo

This file contains various auxiliary functions related to multiple
precision integers.

*/

/* RCSID("$Id: mpaux.h,v 1.1.1.1 1999/10/27 03:42:44 damien Exp $"); */

#ifndef MPAUX_H
#define MPAUX_H

/* Computes a 16-byte session id in the global variable session_id.
   The session id is computed by concatenating the linearized, msb
   first representations of host_key_n, session_key_n, and the cookie. */
void compute_session_id(unsigned char session_id[16],
			unsigned char cookie[8],
			unsigned int host_key_bits,
			BIGNUM *host_key_n,
			unsigned int session_key_bits,
			BIGNUM *session_key_n);

#endif /* MPAUX_H */
