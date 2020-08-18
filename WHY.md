## Estimate velocity

[Article to estimate velocity of motor with quadrature encoder](https://www.embeddedrelated.com/showarticle/158.php)

To estimate motor end shaft speed, if you read the links related to estimating motor speed with a quadrature encoder, the first solution applied is correct because the high resolution of the encoders is enough.

Resolution of one revolution of the end shaft of the motor.

- Counts per revolution 7 (CPR)
- Motor reduction ratio 380:1 (MRR)
- Quadrature encoder resolution 4 (QER)

1 revolution = CPR * MRR * QER = 7 * 380 * 4 = 
10640 counts

so 

360 degrees / 10640 counts = 0.0338 degrees by count

## Identify motor

See paper for [Identification and Real Time Control of a DC Motor](Documents/Motor/Identification_and_Real_Time_Control_of_a_DC_Motor.pdf)

## Raspberry GPIO pin states on powerup

From this [link](https://raspberrypi.stackexchange.com/questions/51479/gpio-pin-states-on-powerup?answertab=active#tab-top), you can extract the initial state for Raspberry Pi Model A, B, B+, the Compute Module, and the Raspberry Pi Zero because uses the Broadcom BCM2835. In addition, it's the same value for BCM2836 and BCM2837, check on 'The power on state is defined in BCM283X ARM Peripherals page 102' or nearest page.

Related links:
- [Raspberry Official Webpage - BCM2837](https://www.raspberrypi.org/documentation/hardware/raspberrypi/bcm2837/README.md)
- [BCM2837 ARM Peripherals](Documents/Raspberry/BCM2837-ARM-Peripherals.pdf)