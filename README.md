# Zork: ROOM ESCAPE
Custom version from the popular old game "Zork"

Link to repository: https://github.com/theepsi/zork
## About
The game starts, and you are in the middle of a strange room. How can you get out of here? You need to use your logic skills and investigate as much as you can to find the way to escape from that psycopath game.

More information about the game: [Wiki](https://github.com/theepsi/zork/wiki)
## Guide [SPOILER ALERT]
IMPORTANT: Every step can be done in different order, you are only limited by room keys and the size of your inventory. This guide is just a possible actions order to reach the end of the game.

At the very start of the game you need to read a letter that is in the room, in that letter you can find the purpose of the game. Also it will reveal a clue to start investigating. It says 'art', so you need to investigate the picture that is in the room you are. By investigating that picture you will find a security_box that have a little sticker with a label "24h". Also you will notice that the picture is an imitation of a Van Gogh picture (Bedroom in Arles). In this imitation you can see that the bedding is green instead of red, that is another clue.

You need to open this security_box, but if you try, it will tell you that you need a PIN code... Knowing the clue from the security_box (24h) you may investigate the clock and read it, you will find that the digital clock is stuck blinking at 02:27 p.m. So here you have the PIN code for the security_box, but you must take care about the format of the time, it says "24h" and the time is in p.m. Finally you can open the security_box with the 1427 PIN like `open security_box 1427`.

Once you have the security_box unlocked you will find a key ("bkey"). If you read the key, it will tell you that the key works only with south door of the living room. If you go south and unlock the door you will arrive to the bedroom. Here you can read a blackboard that contains an encrypted code, investigate a mattress and investigate a desktop.
First of all, if you investigate the mattress you will see three different-color cushions: red, green and blue. Knowing the clue from the Van Gogh picture, the secret will be on the red one. By investigating the cushion you will find a trigger, an item that is a part of something that can start a flame. Then, if you investigate the desktop you will find a perforated_envelope, that basically is a normal envelope with holes and random letters and arrows. You will need to find something to combine with. You can go back to the living room, investigate the bookcase, find a fake_book and within it, you will find a cardboard containing also random letters and arrows. If you combine those items like `combine perforated_envelope cardboard` (it doesn't matter the order of the items) you will create a 'Dictionary'. Reading it you will have the answer for the blackboard on the bedroom. If you translate by hand the message you will obtain `lift the mattress` (yes, is a command that you need to write once you decode it). By Running that command you will lift the mattress and you will find the "wckey", a key that says that you can open the west door of the living room.

You can go now to the bathroom, at the west of the living room. Here you can only obtain a container from a cabinet. This container can be combined with the trigger you found on the bedroom. If you `combine container trigger` you will obtain a lighter as a result. By reading it, you will know that once you have it you will be able to use the cookers of the kitchen.

Now let's move to the kitchen, that is at east from the living room (no key requirement), you need to investigate the fridge, inside the fridge it will be a freezer, here you can find a ice_cube (a really solid one). Then, you can use the kitchen appliance by typing `turn on cookers`. This will only work if you have a lighter in your pockets.
Now you will be able to `boil ice_cube` to reveal the "stkey". This key will allow you to enter to the storage room at the east of the kitchen.

Here, at the Storage room, you will play the last puzzle of the game. You have 3 vats of water, 'a' with 16L capacity, 'b' with 9L capacity and 'c' with 7L capacity. The 'a' one will be filled. You can not fill any of them with a water source, you just can move water through the vats and you can not spill water. The objective is to have 8L in the 'a' vat and 8L in the 'b' vat.

With this rules you have the commands `show vats` to see the current state of the puzzle (if you want to re check) and the command `move [a|b|c] [a|b|c]` that allows you to move water between vats. It will only move water if the container have water inside and only if the destination vat is not completly filled. Example move: `move a b`

Finally if you complete the puzzle a key will fall to the room, the "wkey". With this key you can go to the north of the living room and win the game.

And that's it!
A piece of cake, isn't it?

Hope you enjoy your ROOM ESCAPE experience.

## Authors
* [Ennio Casas Puglielli](https://github.com/theepsi)
	* email: theepsi@gmail.com

## License

MIT