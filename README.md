CircleRound
=====
The system aimed to assign active group communication on PC environment. Escaping from existing complicated information sharing method, we implemented real time sharing at meeting environment. Circle Round is a tangible device, which can enhance efficiency of communication through multiple access at face-to-face meeting. Unlike web-based cooperative tools, Circle Round can hold attention of communication through physical controlling and turn-taking method.

*Website : http://august209.wixsite.com/circleround
*Demo : https://www.youtube.com/watch?v=xoKrDrE2cow
*Conference Proceeding "CIRCLE ROUND: Flexible Communication using Multiple Access at Face-to-Face Meeting"
: http://dx.doi.org/10.1145/2818052.2874326

Implementation
===
When PCs access to Circle Round, it brings these PCstogether through Wi-Fi. The Circle Round conducts itselfon and off the connection continuously between thecomputers. The device can recognize each position ofPCs. Dual dial has a different function depending on thedirection of the dial. We designed software utilizingopen source-based TightVNC1.
-Lighting message
First, when user activate Circle Round, the device emitsred ambient light. Then the device is ready forconnection with PCs. While setting direction using outerdial, the device is emitting yellow light. After setting, asuser click inner dial, the device emits rainbow light,turning round. This shows meaning that “Circle Roundis operating function now.” In addition, the deviceemits green light, waiting next order. We call eachconditions (1)booting mode, (2)connecting mode(3)activating mode, and (4)standby mode in the ordernamed above.
-View sharing and editing scenario
Each two concentric dials perform different functionsindividually. Outer dial shares view and inner dialqualifies editing authority rotationally. We will explainusing Circle Round in a small group communication asfollows(Figure 1). When PCs connect with the devicethrough Wi-Fi, all PC are ready to perform for sharingand editing at systemic level. After setting direction,when someone turns outer dial(view) to user 2, screenof user 2 display to all users in real-time. After that, when another user turns inner dial to user1, devicequalifies authority to user1. Then user 1 can editcontents of the user 2 now. In that way, membersusing device can experience intuitive feedback. Inaddition, inner dial has ‘click’ function; user can inputexecutive commands and quit all current connections.Computing environment can work in parallel with theexisting personal environment by a toggle key.

References
=====
TightVNC 2.7.10 Windows Version 
: http://www.tightvnc.com

License
=====
GNU General Public License version 3
