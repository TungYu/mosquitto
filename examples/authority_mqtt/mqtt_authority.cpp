#include <cstdio>
#include <cstring>

#include "mqtt_authority.h"
#include <mosquittopp.h>

#define ACCOUNT "abc123"
#define PASSWORD "abc123"

int count = 0;

mqtt_authority::mqtt_authority(const char *id, const char *host, int port) : mosquittopp(id)
{
	int keepalive = 60;

	/* Connect immediately. This could also be done by calling
	 * mqtt_tempconv->connect(). */
	connect(host, port, keepalive);
};

mqtt_authority::~mqtt_authority()
{
}

void mqtt_authority::on_connect(int rc)
{
	char buf[50];
	printf("Please input your account: ");
	scanf("%50s", buf);
	if(strcmp(ACCOUNT, buf) != 0){

		count = count + 1;
		printf("Account incorrect %d\n", count);
		if(count > 2)  printf("Error try\n");
		else disconnect();
	} else {

		printf("Connected with code %d.\n", rc);
		if(rc == 0){
			/* Only attempt to subscribe on a successful connect. */
			subscribe(NULL, "temperature/celsius");
		}
	}
}

void mqtt_authority::on_message(const struct mosquitto_message *message)
{
	double temp_celsius, temp_farenheit;
	char buf[51];

	if(!strcmp(message->topic, "temperature/celsius")){
		memset(buf, 0, 51*sizeof(char));
		/* Copy N-1 bytes to ensure always 0 terminated. */
		memcpy(buf, message->payload, 50*sizeof(char));
		temp_celsius = atof(buf);
		temp_farenheit = temp_celsius*9.0/5.0 + 32.0;
		snprintf(buf, 50, "%f", temp_farenheit);
		publish(NULL, "temperature/farenheit", strlen(buf), buf);
	}
}

void mqtt_authority::on_subscribe(int mid, int qos_count, const int *granted_qos)
{
	printf("Subscription succeeded.\n");
}

