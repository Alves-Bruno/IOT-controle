"""

Lê os valores da serial (joystick/volante) e publica via MQTT

""" 

import serial, sys, time
import paho.mqtt.client as mqtt

#
def map(value, in_min, in_max, out_min, out_max):
    return round(((value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min))

#
DEVICE='/dev/ttyUSB0'
SPEED=9600
BROKER='address'

# 
def open_serial(dev, speed, show_info=False):
    ser = serial.Serial(dev, speed, timeout=1)
    time.sleep(0.5)
    if show_info:
        print ('\nStatus: %s ' % (ser.isOpen()))
        print ('Device: %s ' % (ser.name))
        print ('Settings:\n %s ' % (ser))
    return ser

    
#
if __name__ == "__main__":
    if len(sys.argv) == 2:
        DEVICE = sys.argv[1]
    elif  len(sys.argv) == 3:
        DEVICE = sys.argv[1]
        SPEED = sys.argv[2]

    ser = open_serial(DEVICE, SPEED)

    stop=False

    pub = mqtt.Client()
    pub.connect(BROKER)
    
    try: 
        while True:
            rec = ser.readline().rstrip()
            if rec != '': # rec -> 'x,y'
                # separa os valores
                x = rec.split(',')[0]
                y = rec.split(',')[1]
                # calcula os valores base para os motores
                if (x >= 0):
                    left = y
                    right = y - map(x, 0, 128, 0, y)
                else:
                    left = y + map(x, 0, 128, 0, y)
                    right = y
                # envia para o broker mqtt
                output = 'L=' + str(left) + ',R=' + str(right)
                pub.publish('kt/controle', output)
            if stop():
                break
            time.sleep(0.1)
    except:
        stop = True
        ser.close()
        pub.disconnect()