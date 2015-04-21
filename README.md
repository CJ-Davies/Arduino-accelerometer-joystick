# Arduino-accelerometer-joystick

As discussed in [this blog post](http://cjdavies.org/?p=1056) (includes a video of controlling Second Life from a HMC6434) the USB-to-serial firmware that ships stock on the Arduino R3's ATMega16U2 can be replaced with a USB HID joystick firmware, allowing you to use sensors such as an accelerometer as a 'joystick' for any program that takes USB joystick input.

The MMA8452 example uses the [MMA8453_n0m1](https://github.com/n0m1/MMA8453_n0m1) library for the accelerometer & the [newer LCD library](https://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/Home) for an I2C LCD. The [Comp6DOF_n0m1](https://github.com/n0m1/Comp6DOF_n0m1) library may also come in handy.

The idea & the joystick firmware (as well as the original Arduino firmware) came from [this blog post](http://hunt.net.nz/users/darran/weblog/a3599/).