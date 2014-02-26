# Poor man's pam-script

ssh-pam-script-auth is a simple pam module used to execute script during authentication. Though the script in this repo is for ssh authentication, you can change it to work with other services. **The only requirement is that the script you want to execute must print 1 for PASS or 0 for FAIL to stdout**.

It may help you sharing your proxy server, which uses ssh port forwarding, among your friends in a controlled way.

To use it for ssh authentication, you need to add `account requisite pam_script.so` in `/etc/pam.d/sshd` like this

    auth       include      password-auth
    account    required     pam_nologin.so
    account    requisite     pam_script.so

Then, compile and install `pam_script` and `script` for ssh authentication

    make
    make install

`scriptconf.py` provides a configuration example, you can tailor it to your own needs.

* `admin`: the admin users who will be granted authentication without any precondition.
* `nproc`: the max login number of a user
* `perip`: the max login number from a ip
