#!/bin/sh

judge()
{
    if [ "$1" = "" ]
    then
        echo "unittest fail!"
        exit 1
    else
        echo "successful!"
    fi
}

FWIFI WR_AP_PWD 12345678

judge $(./GetSsid.cgi | grep -E "\{\"ssid\"\:\"(.*)\",\"pwd\":\"(.*)\"}")
echo "GetSsidUnittest successful!"

judge $(echo "{\"ssid\":\"aaa\"}" | ./SetSsid.cgi | grep -E "\{\"result\":\"successful\"\}")
sleep 15
judge $(echo "{\"ssid\":\"\"}" | ./SetSsid.cgi | grep -E "\{\"result\":\"fail\"\}")
judge $(echo "{\"ssid\":\"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\"}" | ./SetSsid.cgi | grep -E "\{\"result\":\"fail\"\}")
judge $(echo "aaa" | ./SetSsid.cgi | grep -E "\{\"result\":\"fail\"\}")
echo "SetSsidUnittest successful!"

judge $(echo "{\"newpwd\":\"11111111\"}" | ./SetPwd.cgi | grep -E "\{\"result\":\"successful\"\}")
sleep 15
judge $(echo "{\"newpwd\":\"1\"}" | ./SetPwd.cgi | grep -E "\{\"result\":\"fail\"\}")
judge $(echo "{\"newpwd\":\"111111111111111111111111111111111111111111111111111111111111\"}" | ./SetPwd.cgi | grep -E "\{\"result\":\"fail\"\}")
judge $(echo "aaa" | ./SetPwd.cgi | grep -E "\{\"result\":\"fail\"\}")
echo "SetPwdUnittest successful!"

judge $(./GetDiagonostic.cgi | grep -E "\{\"voltage\":\"(.*)\",\"serialnumber\":\"(.*)\",\"version\":\"(.*)\",\"Manufacturer\":\"(.*)\",\"partnum\":\"(.*)\",\"partname\":\"(.*)\",\"rig\":\"(.*)\",\"roam\":\"(yes|no)\",\"apnname\":\"(.*)\",\"network\":\"(.*)\",\"sig\":\"([0-5])\",\"time\":\"(.*)\",\"date\":\"(.*)\",\"hdop\":\"(.*)\",\"satellites\":\"(.*)\",\"antstatus\":\"(OK|NOK)\",\"sim\":\"(yes|no)\",\"netname\":\"(.*)\",\"wifimode\":\"(AP|SM)\",\"wifissid\":\"(.*)\",\"channel\":\"(.*)\",\"wifimac\":\"(.*)\",\"clientnum\":\"([0-9]*)\",\"clients\":\"(.*)\",\"btname\":\"(.*)\",\"btmac\":\"(.*)\",\"BTHU\":\"(yes|no)\"\}")
echo "GetDiagonosticUnittest successful!"

echo "unittest successful!"
