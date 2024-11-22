Download Pre-Built: https://www.nexusmods.com/liesofp/mods/197

# Lies of P Boss Rush Mod Instructions

## Important Notes
- **Recommended for NG+0 Only:** A fix for the high riposte bug and damage scaling in NG+ will be included in the next update. Fixed as of Friday, November 22, 2024
- **Boss Progress Tracking:** Boss progress will be tracked as long as the **HOME** key is not pressed. Using a Stargazer or visiting other areas in the game will not reset progress.
- **Next Update Features:** The ability to customize boss types will be included.

---

## Installation Instructions

1. **Place the Mod Files:**
   - Copy the `mods` folder and the provided `dxgi.dll` into your Lies of P `Win64` directory.  
     **Example Path:** `D:\SteamLibrary\steamapps\common\Lies of P\LiesofP\Binaries\Win64\`

2. **Prepare the Required DLL:**
   - Download `dxgi.zip` from the link below (**password: sunbeam**):  
     [Download Link to dxgi.zip](https://fearlessrevolution.com/download/file.php?id=53228&sid=634123fd6ed32b5aa5ab52a419c76eff)  
     [Visit the Author's Page](https://fearlessrevolution.com/viewtopic.php?t=25815)
   - Extract the DLL, rename it to `sunbeam.dll`, and place it in the `mods` folder.
   - Place the accompanying `dxgi.ini` file into the `mods` folder as well.
   - **Note:** Due to the author’s request, the `dxgi.zip` file cannot be included with the mod. Please download it directly from the provided link.

3. **Configure the Boss Rush:**
   - Modify `bossrush.ini` in the `mods` folder to adjust settings such as:
     - Damage dealt to bosses
     - Hotkey assignments  
   - Changes made while the game is running can be applied by pressing the `END` key (restarting the game is not required).

---

## How to Use the Mod

1. **Begin Boss Rush:**
   - Go to the Parade Master arena before starting.
   - Press `INSERT` to spawn the first boss.
   - After defeating a boss, press `INSERT` again to spawn the next one.

2. **Restart Boss Rush:**
   - Press `HOME` to reset the boss rush and start from the beginning.

3. **Special Boss Mechanics:**
   - **Green Swamp Monster Boss:** The second phase will automatically spawn after the first phase is defeated. Do not press `INSERT` unless you want a duo fight.
   - **Black Rabbit Brotherhood:** Minions will automatically spawn. Do not press `INSERT` for them.

4. **Tracking Progress:**
   - Progress is saved upon death. The last boss will still be waiting when you respawn.
   - To restart progress, defeat the current boss and press `HOME`.

5. **Apply Changes Mid-Game:**
   - After editing the `bossrush.ini` file, press the `END` key to apply changes without restarting the game.

6. **Repeat the Cycle:**
   - Once the last boss is defeated, pressing `INSERT` will restart the boss rush.

---

## Credits
- **Fiend Busa** - Creator of the Boss Rush mod.
- **Sunbeam** - Provided tools to expose Unreal Engine objects. ([Details](https://fearlessrevolution.com/viewtopic.php?t=25815))
- **Samjviana** - Created the mod loader. ([Mod Loader](https://www.nexusmods.com/grounded/mods/149))
- **DEBUGG0x64** - Provided the damage address. ([Details](https://www.nexusmods.com/liesofp/mods/126?tab=files))

---

## Resources
- **Virtual Key Codes for Hotkey Modification:**  
  [Virtual Key Codes Documentation](https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes)
- **Boss Rush Mod Source Code:**  
  [GitHub Repository](https://github.com/FiendBusa/Lies-Of-P-Boss-Rush)

---

## `bossrush.ini` Template

If you need to create the `bossrush.ini` file from scratch, use the following content:

```ini
[GENERAL]
; REDUCE DAMAGE DEALT (HIGHER = MORE DAMAGE)
ReduceDamage = 150

; WHAT KEY TO SPAWN IN NEXT BOSS
; 0x2D = INSERT
SpawnBoss = 0x2D

; BOSS RUSH WILL AUTOMATICALLY RESET AT THE FINAL BOSS BUT IF YOU WANT TO START FROM THE BEGINNING FOR WHATEVER REASON
; PRESS THIS KEY
; 0x24 = HOME
ResetRush = 0x24

; Reloads INI CONFIG (SO YOU DON’T HAVE TO REBOOT THE GAME TO APPLY NEW CHANGES)
; 0x23 = END
ReloadConfig = 0x23

; CURRENTLY DISABLED AS IT HAS A FEW BUGS
; Play your own boss rush music (make sure to set in-game music volume to 0)
; Set PlayCustomMusic = TRUE and set the path (e.g., CustomMusicPath = "C:\MUSIC\MYRUSHMUSIC.WAV")
; WAV FORMAT ONLY
PlayCustomMusic = FALSE
CustomMusicPath = D:\SteamLibrary\steamapps\common\Lies of P\LiesofP\Binaries\Win64\mods\romeo.wav
Volume = 0.25
