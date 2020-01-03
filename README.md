# Pump It Up Portable Arcade Controller

**Powered by an Arduino Leonardo and an Arduino MEGA**

**For use with hands, not feet** (often known as hand pump)

Designed with the 5-panel "Pump It Up" style in mind, but can also be used as a 4 panel Stepmania/DDR controller when rotated 45 degrees.

## Objective

Pump It Up, and other dance games, require days of rest so your body can recover. Often times I won't play more than 3 times a week. Having a smaller version to use with your hands help with learning crossovers, practice timing and reading ability on days you don't play.

It is worth mentioning that "hand pump" doesn't click immediately for everyone. But for me, practicing crossover patterns with my hands really helps when I transition over to the real thing.

With this README (by the time I finish it...), I intend to guide you through the building process and why I chose certain design decisions, and what I've learned along the way. I am a Computer Scientist with limited hardware knowledge, so you'll be able to tell how I encountered a problem (like how the Arduino MEGA can't act as a keyboard device), and solved it quickly (by adding an Arduino Leonardo to the circuit and communicate with the MEGA over TX/RX pins). There are obviously better ways to build this, but you'll get a good idea of what is needed to build any kind of controller with buttons and cool lights, and maybe learn something new.
