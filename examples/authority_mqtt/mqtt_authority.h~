#ifndef MQTT_AUTHORITY_H
#define MQTT_AUTHORITY_H

#include <mosquittopp.h>

class mqtt_authority : public mosqpp::mosquittopp
{
	public:
		mqtt_authority(const char *id, const char *host, int port);
		~mqtt_authority();

		void on_connect(int rc);
		void on_message(const struct mosquitto_message *message);
		void on_subscribe(int mid, int qos_count, const int *granted_qos);
};

#endif
