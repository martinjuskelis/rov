import smbus
import time
import pygame


# for RPI version 1, use "bus = smbus.SMBus(0)"
bus = smbus.SMBus(1)

# This is the address we setup in the Arduino Program
address = 0x04

pygame.init()
pygame.joystick.init()
joystick = pygame.joystick.Joystick(0)
joystick.init()

print (joystick.get_name)

def writeNumber(value):
	bus.write_byte(address, value)
	# bus.write_byte_data(address, 0, value)
	return -1

def readNumber():
	number = bus.read_byte(address)
	number = bus.read_byte_data(address, 1)
	return number

while True:
        try:
                pygame.event.pump()

		axis_forward_back = 1
		axis_left_right = 0
		axis_up_down = 2
		axis_twist = 3
		

		forwLeft = joystick.get_axis(axis_forward_back) * 63 + 64
		writeNumber(forwLeft)
		time.sleep(0.005)
		
		forwRight = joystick.get_axis(axis_forward_back) * 63 + 64
		writeNumber(forwLeft)
		time.sleep(0.005)

		vertLeft = joystick.get_axis(axis_up_down) * 63 + 64
		writeNumber(forwLeft)
		time.sleep(0.005)
		
		vertRight = joystick.get_axis(axis_up_down) * 63 + 64
		writeNumber(forwLeft)
		time.sleep(0.005)

        except:
                print('error!')
                
