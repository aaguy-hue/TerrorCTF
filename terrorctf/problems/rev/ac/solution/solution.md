# Solution - Animal Crossing: Revenge of the Player

## What to Do?
Exploring the game a bit, we find the following information:
 - The general store has the flag
 - The tailor shop seems to be part of the game and nothing more
   - We have no inputs or anything here, and nothing seems particularly suspicious about it
 - Tom Nook's vault seems to contain something, we likely want to find the password to it
 - The museum is likely is hiding the password to Tom Nook's vault 
   - The guards mention that there is a "sticker" in the museum with the password

## Getting Tom Nook's vault password

### Finding a Vulnerability
The museum seems rather suspicious.

Putting it through a static analysis tool like Ghidra, we find that there is a museum function. The museum function appears to call a donateSpecimen() function, which one would assume handles the code for donating a specimen.

In this function, we get some input (the specimen to donate) and then use `printf` and pass in the input as its only argument. Aha! This is clearly a **format string vulnerability**. A useful article on format strings is at (ctf101)[https://ctf101.org/binary-exploitation/what-is-a-format-string-vulnerability/]. 

### Possibility 1
See `solve.py` for a potential solution script.

After waiting ~10 minutes, you should get that the password to the vault is 0xbadf00d (when you put `%54$llx` as input)

### Possibility 2
Spam `%x` a bunch of times into the input in for donation in the museum, looking through this you see badf00d, although it's a lot more obvious than when using the script in my opinion.

## Getting Infinite Money
Now, go to Tom Nook's Vault and enter the password (case insensitive). You now have infinite money.

## Getting the Flag
Unfortunately, Timmy and Tommy won't let you into their general store. Head over to the tailor shop first and get some free clothes from the Able Sisters. Head back to the general store and purchase the flag in order to get the answer.

`dnCTF{4n1m4l_cr0ss1ng_1s_th3_b3st_g4m3_96024}`
