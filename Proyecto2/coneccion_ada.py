import serial
from Adafruit_IO import Client

#Conexión con AdaFruit_IO
dashboard = Client('nav22250','aio_eHLV65F7zAjA0TCYNL0cfFKf1BxO')
#Conexión con ATMEGA328P
arduino=serial.Serial(port='COM5',baudrate=9600,timeout=None)

servo1=dashboard.receive('servo1')
servo2=dashboard.receive('servo2')
servo3=dashboard.receive('servo3')
servo4=dashboard.receive('servo4')


while True:
    #Loop infinito
    activo = arduino.read()
    print (activo)
    if (activo==b'1'):
        servo1=dashboard.receive('servo1')
        print ('Servo 1: ',(servo1.value).zfill(3))
        arduino.write(str((servo1.value).zfill(3)).encode('utf-8'))

    if (activo==b'2'):
        servo2=dashboard.receive('servo2')
        print ('Servo 2: ',(servo2.value).zfill(3))
        arduino.write(str((servo2.value).zfill(3)).encode('utf-8'))

    if (activo==b'3'):

        servo3=dashboard.receive('servo3')
        print ('Servo 3: ',(servo3.value).zfill(3))
        arduino.write(str((servo3.value).zfill(3)).encode('utf-8'))

    if (activo==b'4'):

        servo4=dashboard.receive('servo4')
        print ('Servo 4: ',(servo4.value).zfill(3))
        arduino.write(str((servo4.value).zfill(3)).encode('utf-8'))
    
    else:
        pass