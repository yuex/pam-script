/* Define which PAM interfaces we provide */
#define PAM_SM_ACCOUNT
#define PAM_SM_AUTH
#define PAM_SM_PASSWORD
#define PAM_SM_SESSION

/* Include PAM headers */
#include <security/pam_appl.h>
#include <security/pam_modules.h>

/* PAM entry point for session creation */
int pam_sm_open_session(pam_handle_t *pamh, int flags, int argc, const char **argv) {
        return(PAM_IGNORE);
}

/* PAM entry point for session cleanup */
int pam_sm_close_session(pam_handle_t *pamh, int flags, int argc, const char **argv) {
        return(PAM_IGNORE);
}

/* PAM entry point for accounting */
int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv) {
  return pam_sm_authenticate(pamh, flags, argc, argv);
}

#include <unistd.h>
#include <stdio.h>
#include <pwd.h>
#include <string.h>
#include <stdlib.h>

#define BUFF_SIZE 1024
#define SCRIPT "/etc/security/script"

/* PAM entry point for authentication verification */
int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv) {
  struct passwd *pw = NULL, pw_s;
  const char *user = NULL;
  int pgu_ret, gpn_ret, pgi_ret;

  pgu_ret = pam_get_user(pamh, &user, NULL);
  if (pgu_ret != PAM_SUCCESS || user == NULL) {
    return(PAM_PERM_DENIED);
  }

  const void *void_from = NULL;

  pgi_ret = pam_get_item(pamh, PAM_RHOST, &void_from);
  if (pgi_ret != PAM_SUCCESS) {
    return(PAM_PERM_DENIED);
  }

  char cmd[BUFF_SIZE] = SCRIPT;
  int end;

  if (!strcat( cmd, " " ) || !strcat( cmd, user ) ||
      !strcat( cmd, " " ) || !strcat( cmd, void_from ))
    return(PAM_PERM_DENIED);

  /*system(cmd);*/

  /*return(PAM_PERM_DENIED);*/

  FILE *result = NULL;
  if ( (result = popen(cmd, "r")) != NULL && 
      fgets(cmd, sizeof(cmd), result) ) {
    pclose(result);
    if (cmd[end = strlen(cmd)-1] != '\n')
      return(PAM_PERM_DENIED); /*line too long*/
    else
      cmd[end] = '\0';
    if (atoi(cmd)==1) 
      return(PAM_SUCCESS);
    else
      return(PAM_PERM_DENIED);
  }
  return(PAM_PERM_DENIED);
}

/*
   PAM entry point for setting user credentials (that is, to actually
   establish the authenticated user's credentials to the service provider)
 */
int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv) {
        return(PAM_IGNORE);
}

/* PAM entry point for authentication token (password) changes */
int pam_sm_chauthtok(pam_handle_t *pamh, int flags, int argc, const char **argv) {
        return(PAM_IGNORE);
}

