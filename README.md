# esp8266_jenkins
ESP8266 jenkins status

## Jenkins plugins
 * [HTTP Request Plugin](https://wiki.jenkins-ci.org/display/JENKINS/HTTP+Request+Plugin)
 * [Any Build Step Plugin](https://wiki.jenkins-ci.org/display/JENKINS/Any+Build+Step+Plugin)


## Jenkins API
https://{{host}}/job/{{job}}/lastBuild/api/json?tree=result,id,building,fullDisplayName,description,number,timestamp,duration
