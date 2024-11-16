Download Pre-Built: https://www.nexusmods.com/liesofp/mods/197

Lies of P Boss Rush Mod Instructions

Important Notes:
Recommended for NG+0 Only: A fix for the high riposte bug and damage scaling in NG+ will be included in the next update.
Boss Progress Tracking: Boss progress will be tracked as long as the HOME key is not pressed. Using a Stargazer or visiting other areas in the game will not reset progress.
Next Update Features: The ability to customize boss types will be included.
Installation Instructions
Place the Mod Files:
Copy the mods folder and the provided dxgi.dll into your Lies of P Win64 directory.
Example path: D:\SteamLibrary\steamapps\common\Lies of P\LiesofP\Binaries\Win64\

Prepare the Required DLL:
Download dxgi.zip from the link below (password: sunbeam):
Download Link to dxgi.zip
Visit the Author's Page
Extract the DLL, rename it to sunbeam.dll, and place it in the mods folder.
Place the accompanying dxgi.ini file into the mods folder as well.
Note: Due to the author’s request, the dxgi.zip file cannot be included with the mod. Please download it directly from the provided link.

Configure the Boss Rush:
Modify bossrush.ini in the mods folder to adjust settings such as:
Damage dealt to bosses
Hotkey assignments
Changes made while the game is running can be applied by pressing the END key (restarting the game is not required).

How to Use the Mod
Begin Boss Rush:
Go to the Parade Master arena before starting.
Press INSERT to spawn the first boss.
After defeating a boss, press INSERT again to spawn the next one.

Restart Boss Rush:
Press HOME to reset the boss rush and start from the beginning.

Special Boss Mechanics:
Green Swamp Monster Boss: The second phase will automatically spawn after the first phase is defeated. Do not press INSERT unless you want a duo fight.
Black Rabbit Brotherhood: Minions will automatically spawn. Do not press INSERT for them.

Tracking Progress:
Progress is saved upon death. The last boss will still be waiting when you respawn.
To restart progress, defeat the current boss and press HOME.

Apply Changes Mid-Game:
After editing the bossrush.ini file, press the END key to apply changes without restarting the game.

Repeat the Cycle:
Once the last boss is defeated, pressing INSERT will restart the boss rush.

Credits
Fiend Busa - Creator of the Boss Rush mod.
Sunbeam - Provided tools to expose Unreal Engine objects. (Details)
Samjviana - Created the mod loader. (Mod Loader)
DEBUGG0x64 - Provided the damage address. (Details)



bossrush.ini Template

[GENERAL]
; REDUCE DAMAGE DEALT (HIGHER = MORE DAMAGE)
ReduceDamage = 150

;WHAT KEY TO SPAWN IN NEXT BOSS
;0x2D = INSERT
SpawnBoss = 0x2D

;BOSS RUSH WILL AUTOMATICALLY RESET AT THE FINAL BOSS BUT IF YOU WANT TO START FROM THE BEGGINING FOR WHATEVER REASON
PRESS THIS KEY
; 0x24 = HOME
ResetRush = 0x24

;Reloads INI CONFIG (SO YOU DONT HAVE TO REBOOT THE GAME TO APPLY NEW CHANGES)
; 0x23 = END
ReloadConfig = 0x23

;CURRENTLY DISABLED AS IT HAS A FEW BUGS
;Play your own boss rush music (make sure to set in game music volume to 0
;set PlayCustomMusic = TRUE and set the path I.E CustomMusicPath = "C:\MUSIC\MYRUSHMUSIC.WAV"
; WAV FORMAT ONLY
PlayCustomMusic = FALSE
CustomMusicPath = D:\SteamLibrary\steamapps\common\Lies of P\LiesofP\Binaries\Win64\mods\romeo.wav
Volume = 0.25
