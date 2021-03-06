#include "mqtt_authority.h"

int main(int argc, char *argv[])
{
	class mqtt_authority *authority;
	int rc;

	mosqpp::lib_init();

	authority = new mqtt_authority("tempconv", "localhost", 1883);
	
	while(1){
		rc = authority->loop();
		if(rc){
			authority->reconnect();
		}
	}

	mosqpp::lib_cleanup();

	return 0;
}

