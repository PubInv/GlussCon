---
layout: default
title: GlussCon/TetroCon -- A Gluss/Tetrobot Controller
---


# GlussCon


This is a project of Public Invention in support of [The Gluss Project](http://pubinv.github.io/gluss/), a radical approach to robotics trying
to build a general purpose metamorphic machine. Like all Public Invention projects, it is completely open-source and does not seek patents.

The Tetrobot Controller, or TetroCon, explores the possibility of building a hand-manipulable controller which is a puppet or doll--a miniature version of
the larger GlussBot/Tetrobot which is to be controlled.  By pushing the TetroCon into position with the hands, the GlussBot/TetroBot can be instructed to assume the same
configuration (but on a large scale.)  The hope is that in this way a work person can easily control the GlussBot/Tetrobot in doing tasks that would otherwise
be difficult to specify.

The GlussCon project is led by Evan Bartilson and Joshua Hannan, with input from Robert L. Read.

<iframe width="560" height="315" src="https://www.youtube.com/embed/B5CEYXGaeq0" frameborder="0" allowfullscreen></iframe>

# Progess So Far

The GlussCon project is just beginning.  



The current system functions to remote controller the first tetrahedron of the glussbot robot.  The system consists of the 3D printable parts that implement
the turret joint while holding linear potentiometers. The pots are multiplexed through a 16 channel MUX chip (only 6 channels in use presently). They are
read through a standard Arduino Uno. This has a Sparkfun ESP8266 WIFI shield, which responds to http requests by returning all pot values in JSON.
We then read these values and send them to the Tetrobot using a control program that you can find at the Gluss github Repo.

# Plans

Our initial plans right now are to:
* Expand to a full 7-Tet controller
* Decrease the lag time by improving the WIFI (and other delays)
* Continue playing to understand how to best use this concept


<img width="60%" src="./images/GlussConTet.jpg"/>

# How to Contribute

We welcome your participation, in either the GlussCon project, the Gluss project, or one of the other Public Invention projects.
To discuss the GlussCon project specifically, email Joshua Hannan 
<hannanjoshua19@gmail.com> (Github: [joshuahannah](https://github.com/joshuahannan)) or Evan Bartilson <ebartilson@utexas.edu>.

You are welcome to email Robert L. Read <read.robert@gmail.com> to discuss how you can help the Public Invention projects in general.

However, as a public projects, it is even better for you to comment publicly
on these projects.
You can do this by opening an ("issue")[https://github.com/PubInv/PubInv/issues] here at GitHub.  If you want to add to or improve one of the existing documents, you can do this with a "pull request".

You may wish to subscribe to our <a href="https://www.youtube.com/watch?v=1T8XSMhwKUE">YouTube Channel</a>. Since we are bound neither by the need to keep something secret due to patent restrictions imposed by Universities, nor by the formality of Academic publishing, nor by the need to maintain trade secrets, we publish informally a lot at YouTube.

