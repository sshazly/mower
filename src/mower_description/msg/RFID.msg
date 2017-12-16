# RFID tag reading from an active RFTag that emits energy and reports
# one range reading at the distance measured along with a unique tag id. 

Header header           # timestamp in the header is the time the ranger
                        # returned the distance reading

float32 min_range       # minimum range value [m]
float32 max_range       # maximum range value [m]
                        # Fixed distance rangers require min_range==max_range

float32 range           # range data [m]
                        # (Note: values < range_min or > range_max
                        # should be discarded)
                        # Fixed distance rangers only output -Inf or +Inf.
                        # -Inf represents a detection within fixed distance.
                        # (Detection too close to the sensor to quantify)
                        # +Inf represents no detection within the fixed distance.
                        # (Object out of range)

uint8 id                # the unique ID of the tag [enum]
