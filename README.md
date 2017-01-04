CircleRound
=====
This system helps active communication within an offline group in a PC environment. Escaping from existing complicated information sharing method, we implemented real-time sharing in the meeting environment. Circle Round is a tangible device, which can enhance the efficiency of communication through multiple access at face-to-face meetings. Unlike web-based cooperative tools, Circle Round can hold attention of communication through physical control and turn-taking methods.

*Documentation(slideshare) : http://www.slideshare.net/secret/oerwmDS5PCLfY6

*Website : http://august209.wixsite.com/circleround

*Demo : https://www.youtube.com/watch?v=xoKrDrE2cow

*CSCW'16 Proceeding "CIRCLE ROUND: Flexible Communication using Multiple Access at Face-to-Face Meeting"<br>
: http://dx.doi.org/10.1145/2818052.2874326


Implementation
===
When PCs access to Circle Round, it brings these PCs together through Wi-Fi. The Circle Round conducts itself on and off the connection continuously between the computers. The device can recognize each position of PCs. Dual dial has a different function depending on the direction of the dial. We designed software utilizing open source-based TightVNC.

-Lighting message<br>
First, when user activate Circle Round, the device emitsred ambient light. Then the device is ready for connection with PCs. While setting direction using outer-dial, the device is emitting yellow light. After setting, asuser click inner-dial, the device emits rainbow light,turning round. This shows meaning that “Circle Roundis operating function now.” In addition, the device emits green light, waiting next order. We call eachconditions (1)booting mode, (2)connecting mode, (3)activating mode, and (4)standby mode in the ordernamed above.

-View sharing and editing scenario<br>
Each two concentric dials perform different functions individually. Outer dial shares view and inner dial qualifies editing authority rotationally. We will explainuse Circle Round in a small group communication as follows. When PCs connect with the device through Wi-Fi, all PC are ready to perform for sharingand editing at systemic level. After setting direction, when someone turns outer-dial(view) to user2, screen of user2 display to all users in real-time. After that, when another user turns inner-dial to user1, device qualifies authority to user1. Then user1 can edit contents of the user2 now. In that way, members using device can experience intuitive feedback. In addition, inner-dial has ‘click’ function; user can input executive commands and quit all current connections. Computing environment can work in parallel with the existing personal environment by a toggle key.

How to use
====
Now Progressing

References
=====
TightVNC 2.7.10 (Windows Version) <br>
: http://www.tightvnc.com

License
=====
GNU General Public License version 3
