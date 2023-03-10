/*

ssh.h

Author: Tatu Ylonen <ylo@cs.hut.fi>

Copyright (c) 1995 Tatu Ylonen <ylo@cs.hut.fi>, Espoo, Finland
                   All rights reserved

Created: Fri Mar 17 17:09:37 1995 ylo

Generic header file for ssh.

*/

/* RCSID("$Id: ssh.h,v 1.1.1.1 1999/10/27 03:42:45 damien Exp $"); */

#ifndef SSH_H
#define SSH_H

#include "rsa.h"
#include "cipher.h"

/* The default cipher used if IDEA is not supported by the remote host. 
   It is recommended that this be one of the mandatory ciphers (DES, 3DES),
   though that is not required. */
#define SSH_FALLBACK_CIPHER	SSH_CIPHER_3DES

/* Cipher used for encrypting authentication files. */
#define SSH_AUTHFILE_CIPHER	SSH_CIPHER_3DES

/* Default port number. */
#define SSH_DEFAULT_PORT	22

/* Maximum number of TCP/IP ports forwarded per direction. */
#define SSH_MAX_FORWARDS_PER_DIRECTION	100

/* Maximum number of RSA authentication identity files that can be specified
   in configuration files or on the command line. */
#define SSH_MAX_IDENTITY_FILES		100

/* Major protocol version.  Different version indicates major incompatiblity
   that prevents communication.  */
#define PROTOCOL_MAJOR		1

/* Minor protocol version.  Different version indicates minor incompatibility
   that does not prevent interoperation. */
#define PROTOCOL_MINOR		5

/* Name for the service.  The port named by this service overrides the default
   port if present. */
#define SSH_SERVICE_NAME	"ssh"

#ifndef ETCDIR
#define ETCDIR			"/etc"
#endif /* ETCDIR */

#define PIDDIR			"/var/run"

/* System-wide file containing host keys of known hosts.  This file should be
   world-readable. */
#define SSH_SYSTEM_HOSTFILE	ETCDIR "/ssh_known_hosts"

/*  HOST_KEY_FILE		/etc/ssh_host_key,
    SERVER_CONFIG_FILE		/etc/sshd_config,
and HOST_CONFIG_FILE		/etc/ssh_config
are all defined in Makefile.in.  Of these, ssh_host_key should be readable
only by root, whereas ssh_config should be world-readable. */

#define HOST_KEY_FILE		ETCDIR "/ssh_host_key"
#define SERVER_CONFIG_FILE	ETCDIR "/sshd_config"
#define HOST_CONFIG_FILE	ETCDIR "/ssh_config"

#define SSH_PROGRAM		"/usr/bin/ssh"

/* The process id of the daemon listening for connections is saved
   here to make it easier to kill the correct daemon when necessary. */
#define SSH_DAEMON_PID_FILE	PIDDIR "/sshd.pid"

/* The directory in user\'s home directory in which the files reside.
   The directory should be world-readable (though not all files are). */
#define SSH_USER_DIR		".ssh"

/* Per-user file containing host keys of known hosts.  This file need
   not be readable by anyone except the user him/herself, though this does
   not contain anything particularly secret. */
#define SSH_USER_HOSTFILE	"~/.ssh/known_hosts"

/* Name of the default file containing client-side authentication key. 
   This file should only be readable by the user him/herself. */
#define SSH_CLIENT_IDENTITY	".ssh/identity"

/* Configuration file in user\'s home directory.  This file need not be
   readable by anyone but the user him/herself, but does not contain
   anything particularly secret.  If the user\'s home directory resides
   on an NFS volume where root is mapped to nobody, this may need to be
   world-readable. */
#define SSH_USER_CONFFILE	".ssh/config"

/* File containing a list of those rsa keys that permit logging in as
   this user.  This file need not be
   readable by anyone but the user him/herself, but does not contain
   anything particularly secret.  If the user\'s home directory resides
   on an NFS volume where root is mapped to nobody, this may need to be
   world-readable.  (This file is read by the daemon which is running as 
   root.) */
#define SSH_USER_PERMITTED_KEYS	".ssh/authorized_keys"

/* Per-user and system-wide ssh "rc" files.  These files are executed with
   /bin/sh before starting the shell or command if they exist.  They
   will be passed "proto cookie" as arguments if X11 forwarding with
   spoofing is in use.  xauth will be run if neither of these exists. */
#define SSH_USER_RC		".ssh/rc"
#define SSH_SYSTEM_RC		ETCDIR "/sshrc"

/* Ssh-only version of /etc/hosts.equiv. */
#define SSH_HOSTS_EQUIV		ETCDIR "/shosts.equiv"

/* Additionally, the daemon may use ~/.rhosts and /etc/hosts.equiv if 
   rhosts authentication is enabled. */

/* Name of the environment variable containing the pathname of the
   authentication socket. */
#define SSH_AUTHSOCKET_ENV_NAME	"SSH_AUTH_SOCK"

/* Force host key length and server key length to differ by at least this
   many bits.  This is to make double encryption with rsaref work. */
#define SSH_KEY_BITS_RESERVED		128

/* Length of the session key in bytes.  (Specified as 256 bits in the 
   protocol.)  */
#define SSH_SESSION_KEY_LENGTH		32

/* Name of Kerberos service for SSH to use. */
#define KRB4_SERVICE_NAME		"rcmd"

/* Authentication methods.  New types can be added, but old types should not
   be removed for compatibility.  The maximum allowed value is 31. */
#define SSH_AUTH_RHOSTS		1
#define SSH_AUTH_RSA		2
#define SSH_AUTH_PASSWORD	3
#define SSH_AUTH_RHOSTS_RSA	4
				/* 5 is TIS */
#define SSH_AUTH_KERBEROS	6
#define SSH_PASS_KERBEROS_TGT	7
				/* 8 to 15 are reserved */
#define SSH_PASS_AFS_TOKEN	21

/* Protocol flags.  These are bit masks. */
#define SSH_PROTOFLAG_SCREEN_NUMBER	1 /* X11 forwarding includes screen */
#define SSH_PROTOFLAG_HOST_IN_FWD_OPEN	2 /* forwarding opens contain host */

/* Definition of message types.  New values can be added, but old values
   should not be removed or without careful consideration of the consequences
   for compatibility.  The maximum value is 254; value 255 is reserved
   for future extension. */
/* Message name */			/* msg code */  /* arguments */
#define SSH_MSG_NONE				0	/* no message */
#define SSH_MSG_DISCONNECT			1	/* cause (string) */
#define SSH_SMSG_PUBLIC_KEY			2	/* ck,msk,srvk,hostk */
#define SSH_CMSG_SESSION_KEY			3	/* key (BIGNUM) */
#define SSH_CMSG_USER				4	/* user (string) */
#define SSH_CMSG_AUTH_RHOSTS			5	/* user (string) */
#define SSH_CMSG_AUTH_RSA			6	/* modulus (BIGNUM) */
#define SSH_SMSG_AUTH_RSA_CHALLENGE		7	/* int (BIGNUM) */
#define SSH_CMSG_AUTH_RSA_RESPONSE		8	/* int (BIGNUM) */
#define SSH_CMSG_AUTH_PASSWORD			9	/* pass (string) */
#define SSH_CMSG_REQUEST_PTY		        10	/* TERM, tty modes */
#define SSH_CMSG_WINDOW_SIZE		        11	/* row,col,xpix,ypix */
#define SSH_CMSG_EXEC_SHELL			12	/* */
#define SSH_CMSG_EXEC_CMD			13	/* cmd (string) */
#define SSH_SMSG_SUCCESS			14	/* */
#define SSH_SMSG_FAILURE			15	/* */
#define SSH_CMSG_STDIN_DATA			16	/* data (string) */
#define SSH_SMSG_STDOUT_DATA			17	/* data (string) */
#define SSH_SMSG_STDERR_DATA			18	/* data (string) */
#define SSH_CMSG_EOF				19	/* */
#define SSH_SMSG_EXITSTATUS			20	/* status (int) */
#define SSH_MSG_CHANNEL_OPEN_CONFIRMATION	21	/* channel (int) */
#define SSH_MSG_CHANNEL_OPEN_FAILURE		22	/* channel (int) */
#define SSH_MSG_CHANNEL_DATA			23	/* ch,data (int,str) */
#define SSH_MSG_CHANNEL_CLOSE			24	/* channel (int) */
#define SSH_MSG_CHANNEL_CLOSE_CONFIRMATION	25	/* channel (int) */
/*      SSH_CMSG_X11_REQUEST_FORWARDING         26         OBSOLETE */
#define SSH_SMSG_X11_OPEN			27	/* channel (int) */
#define SSH_CMSG_PORT_FORWARD_REQUEST		28	/* p,host,hp (i,s,i) */
#define SSH_MSG_PORT_OPEN			29	/* ch,h,p (i,s,i) */
#define SSH_CMSG_AGENT_REQUEST_FORWARDING	30	/* */
#define SSH_SMSG_AGENT_OPEN			31	/* port (int) */
#define SSH_MSG_IGNORE				32	/* string */
#define SSH_CMSG_EXIT_CONFIRMATION		33	/* */
#define SSH_CMSG_X11_REQUEST_FORWARDING		34	/* proto,data (s,s) */
#define SSH_CMSG_AUTH_RHOSTS_RSA		35	/* user,mod (s,mpi) */
#define SSH_MSG_DEBUG				36	/* string */
#define SSH_CMSG_REQUEST_COMPRESSION		37	/* level 1-9 (int) */
#define SSH_CMSG_MAX_PACKET_SIZE		38	/* size 4k-1024k (int) */
#define SSH_CMSG_AUTH_TIS			39	/* this is proto-1.5, but we ignore TIS */
#define SSH_SMSG_AUTH_TIS_CHALLENGE		40
#define SSH_CMSG_AUTH_TIS_RESPONSE		41

#define SSH_CMSG_AUTH_KERBEROS			42	/* (KTEXT) */
#define SSH_SMSG_AUTH_KERBEROS_RESPONSE		43	/* (KTEXT) */
#define SSH_CMSG_HAVE_KERBEROS_TGT		44	/* credentials (s) */
#define SSH_CMSG_HAVE_AFS_TOKEN			65	/* token (s) */


/* Includes that need definitions above. */

#include "readconf.h"

/*------------ definitions for login.c -------------*/

/* Returns the time when the user last logged in.  Returns 0 if the 
   information is not available.  This must be called before record_login. 
   The host from which the user logged in is stored in buf. */
unsigned long get_last_login_time(uid_t uid, const char *logname, 
				  char *buf, unsigned int bufsize);

/* Records that the user has logged in.  This does many things normally
   done by login(1). */
void record_login(int pid, const char *ttyname, const char *user, uid_t uid,
		  const char *host, struct sockaddr_in *addr);

/* Records that the user has logged out.  This does many thigs normally
   done by login(1) or init. */
void record_logout(int pid, const char *ttyname);

/*------------ definitions for sshconnect.c ----------*/

/* Opens a TCP/IP connection to the remote server on the given host.  If
   port is 0, the default port will be used.  If anonymous is zero,
   a privileged port will be allocated to make the connection. 
   This requires super-user privileges if anonymous is false. 
   Connection_attempts specifies the maximum number of tries, one per
   second.  This returns true on success, and zero on failure.  If the
   connection is successful, this calls packet_set_connection for the
   connection. */
int ssh_connect(const char *host, struct sockaddr_in *hostaddr,
		int port, int connection_attempts,
		int anonymous, uid_t original_real_uid,
		const char *proxy_command);

/* Starts a dialog with the server, and authenticates the current user on the
   server.  This does not need any extra privileges.  The basic connection
   to the server must already have been established before this is called. 
   If login fails, this function prints an error and never returns. 
   This initializes the random state, and leaves it initialized (it will also
   have references from the packet module). */
void ssh_login(int host_key_valid, RSA *host_key, const char *host,
	       struct sockaddr_in *hostaddr, Options *options,
	       uid_t original_real_uid);

/*------------ Definitions for various authentication methods. -------*/

/* Tries to authenticate the user using the .rhosts file.  Returns true if
   authentication succeeds.  If ignore_rhosts is non-zero, this will not
   consider .rhosts and .shosts (/etc/hosts.equiv will still be used). 
   If strict_modes is true, checks ownership and modes of .rhosts/.shosts. */
int auth_rhosts(struct passwd *pw, const char *client_user,
		int ignore_rhosts, int strict_modes);

/* Tries to authenticate the user using the .rhosts file and the host using
   its host key.  Returns true if authentication succeeds. */
int auth_rhosts_rsa(struct passwd *pw, const char *client_user,
		    unsigned int bits, BIGNUM *client_host_key_e,
		    BIGNUM *client_host_key_n, int ignore_rhosts,
		    int strict_modes);

/* Tries to authenticate the user using password.  Returns true if
   authentication succeeds. */
int auth_password(struct passwd *pw, const char *password);

/* Performs the RSA authentication dialog with the client.  This returns
   0 if the client could not be authenticated, and 1 if authentication was
   successful.  This may exit if there is a serious protocol violation. */
int auth_rsa(struct passwd *pw, BIGNUM *client_n, int strict_modes);

/* Parses an RSA key (number of bits, e, n) from a string.  Moves the pointer
   over the key.  Skips any whitespace at the beginning and at end. */
int auth_rsa_read_key(char **cpp, unsigned int *bitsp, BIGNUM *e, BIGNUM *n);

/* Returns the name of the machine at the other end of the socket.  The
   returned string should be freed by the caller. */
char *get_remote_hostname(int socket);

/* Return the canonical name of the host in the other side of the current
   connection (as returned by packet_get_connection).  The host name is
   cached, so it is efficient to call this several times. */
const char *get_canonical_hostname(void);

/* Returns the remote IP address as an ascii string.  The value need not be
   freed by the caller. */
const char *get_remote_ipaddr(void);

/* Returns the port number of the peer of the socket. */
int get_peer_port(int sock);

/* Returns the port number of the remote host. */
int get_remote_port(void);

/* Tries to match the host name (which must be in all lowercase) against the
   comma-separated sequence of subpatterns (each possibly preceded by ! to 
   indicate negation).  Returns true if there is a positive match; zero
   otherwise. */
int match_hostname(const char *host, const char *pattern, unsigned int len);

/* Checks whether the given host is already in the list of our known hosts.
   Returns HOST_OK if the host is known and has the specified key,
   HOST_NEW if the host is not known, and HOST_CHANGED if the host is known
   but used to have a different host key.  The host must be in all lowercase. */
typedef enum { HOST_OK, HOST_NEW, HOST_CHANGED } HostStatus;
HostStatus check_host_in_hostfile(const char *filename, 
				  const char *host, unsigned int bits,
				  BIGNUM *e, BIGNUM *n,
				  BIGNUM *ke, BIGNUM *kn);

/* Appends an entry to the host file.  Returns false if the entry
   could not be appended. */
int add_host_to_hostfile(const char *filename, const char *host,
			 unsigned int bits, BIGNUM *e, BIGNUM *n);

/* Performs the RSA authentication challenge-response dialog with the client,
   and returns true (non-zero) if the client gave the correct answer to
   our challenge; returns zero if the client gives a wrong answer. */
int auth_rsa_challenge_dialog(unsigned int bits, BIGNUM *e, BIGNUM *n);

/* Reads a passphrase from /dev/tty with echo turned off.  Returns the 
   passphrase (allocated with xmalloc).  Exits if EOF is encountered. 
   If from_stdin is true, the passphrase will be read from stdin instead. */
char *read_passphrase(const char *prompt, int from_stdin);

/* Saves the authentication (private) key in a file, encrypting it with
   passphrase.  The identification of the file (lowest 64 bits of n)
   will precede the key to provide identification of the key without
   needing a passphrase. */
int save_private_key(const char *filename, const char *passphrase,
		     RSA *private_key, const char *comment);

/* Loads the public part of the key file (public key and comment). 
   Returns 0 if an error occurred; zero if the public key was successfully
   read.  The comment of the key is returned in comment_return if it is
   non-NULL; the caller must free the value with xfree. */
int load_public_key(const char *filename, RSA *pub, 
		    char **comment_return);

/* Loads the private key from the file.  Returns 0 if an error is encountered
   (file does not exist or is not readable, or passphrase is bad).
   This initializes the private key.  The comment of the key is returned 
   in comment_return if it is non-NULL; the caller must free the value 
   with xfree. */
int load_private_key(const char *filename, const char *passphrase,
		     RSA *private_key, char **comment_return);

/*------------ Definitions for logging. -----------------------*/

/* Supported syslog facilities. */
typedef enum
{
  SYSLOG_FACILITY_DAEMON,
  SYSLOG_FACILITY_USER,
  SYSLOG_FACILITY_AUTH,
  SYSLOG_FACILITY_LOCAL0,
  SYSLOG_FACILITY_LOCAL1,
  SYSLOG_FACILITY_LOCAL2,
  SYSLOG_FACILITY_LOCAL3,
  SYSLOG_FACILITY_LOCAL4,
  SYSLOG_FACILITY_LOCAL5,
  SYSLOG_FACILITY_LOCAL6,
  SYSLOG_FACILITY_LOCAL7
} SyslogFacility;

/* Initializes logging.  If debug is non-zero, debug() will output something.
   If quiet is non-zero, none of these will log send anything to syslog
   (but maybe to stderr). */
void log_init(char *av0, int on_stderr, int debug, int quiet,
	      SyslogFacility facility);

/* Outputs a message to syslog or stderr, depending on the implementation. 
   The format must guarantee that the final message does not exceed 1024 
   characters.  The message should not contain newline. */
void log(const char *fmt, ...);

/* Outputs a message to syslog or stderr, depending on the implementation. 
   The format must guarantee that the final message does not exceed 1024 
   characters.  The message should not contain newline. */
void debug(const char *fmt, ...);

/* Outputs a message to syslog or stderr, depending on the implementation. 
   The format must guarantee that the final message does not exceed 1024 
   characters.  The message should not contain newline. */
void error(const char *fmt, ...);

/* Outputs a message to syslog or stderr, depending on the implementation. 
   The format must guarantee that the final message does not exceed 1024 
   characters.  The message should not contain newline.  
   This call never returns. */
void fatal(const char *fmt, ...);

/* Registers a cleanup function to be called by fatal() before exiting. 
   It is permissible to call fatal_remove_cleanup for the function itself
   from the function. */
void fatal_add_cleanup(void (*proc)(void *context), void *context);

/* Removes a cleanup frunction to be called at fatal(). */
void fatal_remove_cleanup(void (*proc)(void *context), void *context);

/*---------------- definitions for channels ------------------*/

/* Sets specific protocol options. */
void channel_set_options(int hostname_in_open);

/* Allocate a new channel object and set its type and socket.  Remote_name
   must have been allocated with xmalloc; this will free it when the channel
   is freed. */
int channel_allocate(int type, int sock, char *remote_name);

/* Free the channel and close its socket. */
void channel_free(int channel);

/* Add any bits relevant to channels in select bitmasks. */
void channel_prepare_select(fd_set *readset, fd_set *writeset);

/* After select, perform any appropriate operations for channels which
   have events pending. */
void channel_after_select(fd_set *readset, fd_set *writeset);

/* If there is data to send to the connection, send some of it now. */
void channel_output_poll(void);

/* This is called when a packet of type CHANNEL_DATA has just been received.
   The message type has already been consumed, but channel number and data
   is still there. */
void channel_input_data(int payload_len);

/* Returns true if no channel has too much buffered data. */
int channel_not_very_much_buffered_data(void);

/* This is called after receiving CHANNEL_CLOSE. */
void channel_input_close(void);

/* This is called after receiving CHANNEL_CLOSE_CONFIRMATION. */
void channel_input_close_confirmation(void);

/* This is called after receiving CHANNEL_OPEN_CONFIRMATION. */
void channel_input_open_confirmation(void);

/* This is called after receiving CHANNEL_OPEN_FAILURE from the other side. */
void channel_input_open_failure(void);

/* This closes any sockets that are listening for connections; this removes
   any unix domain sockets. */
void channel_stop_listening(void);

/* Closes the sockets of all channels.  This is used to close extra file
   descriptors after a fork. */
void channel_close_all(void);

/* Returns the maximum file descriptor number used by the channels. */
int channel_max_fd(void);

/* Returns true if there is still an open channel over the connection. */
int channel_still_open(void);

/* Returns a string containing a list of all open channels.  The list is
   suitable for displaying to the user.  It uses crlf instead of newlines.
   The caller should free the string with xfree. */
char *channel_open_message(void);

/* Initiate forwarding of connections to local port "port" through the secure
   channel to host:port from remote side.  This never returns if there
   was an error. */
void channel_request_local_forwarding(int port, const char *host,
				      int remote_port);

/* Initiate forwarding of connections to port "port" on remote host through
   the secure channel to host:port from local side.  This never returns
   if there was an error.  This registers that open requests for that
   port are permitted. */
void channel_request_remote_forwarding(int port, const char *host,
				       int remote_port);

/* Permits opening to any host/port in SSH_MSG_PORT_OPEN.  This is usually
   called by the server, because the user could connect to any port anyway,
   and the server has no way to know but to trust the client anyway. */
void channel_permit_all_opens(void);

/* This is called after receiving CHANNEL_FORWARDING_REQUEST.  This initates
   listening for the port, and sends back a success reply (or disconnect
   message if there was an error).  This never returns if there was an 
   error. */
void channel_input_port_forward_request(int is_root);

/* This is called after receiving PORT_OPEN message.  This attempts to connect
   to the given host:port, and sends back CHANNEL_OPEN_CONFIRMATION or
   CHANNEL_OPEN_FAILURE. */
void channel_input_port_open(int payload_len);

/* Creates a port for X11 connections, and starts listening for it.
   Returns the display name, or NULL if an error was encountered. */
char *x11_create_display(int screen);

/* Creates an internet domain socket for listening for X11 connections. 
   Returns a suitable value for the DISPLAY variable, or NULL if an error
   occurs. */
char *x11_create_display_inet(int screen);

/* This is called when SSH_SMSG_X11_OPEN is received.  The packet contains
   the remote channel number.  We should do whatever we want, and respond
   with either SSH_MSG_OPEN_CONFIRMATION or SSH_MSG_OPEN_FAILURE. */
void x11_input_open(int payload_len);

/* Requests forwarding of X11 connections.  This should be called on the 
   client only. */
void x11_request_forwarding(void);

/* Requests forwarding for X11 connections, with authentication spoofing.
   This should be called in the client only.  */
void x11_request_forwarding_with_spoofing(const char *proto, const char *data);

/* Local Xauthority file (server only). */
extern char *xauthfile;

/* Sends a message to the server to request authentication fd forwarding. */
void auth_request_forwarding(void);

/* Returns the name of the forwarded authentication socket.  Returns NULL
   if there is no forwarded authentication socket.  The returned value points
   to a static buffer. */
char *auth_get_socket_name(void);

/* This if called to process SSH_CMSG_AGENT_REQUEST_FORWARDING on the server.
   This starts forwarding authentication requests. */
void auth_input_request_forwarding(struct passwd *pw);

/* This is called to process an SSH_SMSG_AGENT_OPEN message. */
void auth_input_open_request(void);

/* Returns true if the given string matches the pattern (which may contain
   ? and * as wildcards), and zero if it does not match. */
int match_pattern(const char *s, const char *pattern);

/* Expands tildes in the file name.  Returns data allocated by xmalloc.
   Warning: this calls getpw*. */
char *tilde_expand_filename(const char *filename, uid_t my_uid);

/* Performs the interactive session.  This handles data transmission between
   the client and the program.  Note that the notion of stdin, stdout, and
   stderr in this function is sort of reversed: this function writes to
   stdin (of the child program), and reads from stdout and stderr (of the
   child program). */
void server_loop(int pid, int fdin, int fdout, int fderr);

/* Client side main loop for the interactive session. */
int client_loop(int have_pty, int escape_char);

/* Linked list of custom environment strings (see auth-rsa.c). */
struct envstring {
  struct envstring *next;
  char *s;
};

#ifdef KRB4
#include <krb.h>

/* Performs Kerberos v4 mutual authentication with the client. This returns
   0 if the client could not be authenticated, and 1 if authentication was
   successful.  This may exit if there is a serious protocol violation. */
int auth_krb4(const char *server_user, KTEXT auth, char **client);
int ssh_tf_init(uid_t uid);

#ifdef AFS
#include <kafs.h>

/* Accept passed Kerberos v4 ticket-granting ticket and AFS tokens. */
int auth_kerberos_tgt(struct passwd *pw, const char *string);
int auth_afs_token(char *server_user, uid_t uid, const char *string);

int creds_to_radix(CREDENTIALS *creds, unsigned char *buf);
int radix_to_creds(const char *buf, CREDENTIALS *creds);
#endif /* AFS */

#endif /* KRB4 */

#ifdef SKEY
#include <skey.h>
char *skey_fake_keyinfo(char *username);
#endif /* SKEY */

#endif /* SSH_H */
