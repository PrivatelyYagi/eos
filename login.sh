#!/bin/sh

USERID=st071535 #自分の学籍番号
PASSWD=KCGN0001 #自分のパスワード

LOGIN_URL=https://wlc.int.kcg.edu/login.html/

curl --tlsv1.0 ${LOGIN_URL} -d buttonClicked=4 -d username=${USERID} -d password=${PASSWD}
