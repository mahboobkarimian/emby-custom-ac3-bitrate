# Emby Custom AC3 (Dolby Digital) Bitrate (1664000)

This is a hacky fix for this problem

https://emby.media/community/index.php?/topic/67030-adjust-bitrate-for-transcoded-audio-such-as-dolby-ac-3

My solution is to replace the **ffmpeg** binary with a wrapper that manipulates incoming arguments and then actually runs ffmpeg.

It looks for arguments `-c:a:? ac3` then replaces `-ab:a:? ??????` with `-ab:a:? 1664000` or whatever you set `EMBY_CUSTOM_AC3_BITRATE` to.

## Using in Linux

Navigate to `/opt/emby-server/bin`. Rename the original `ffmpeg` to `_ffmpeg`. <br> 
Compile using `gcc ffmpeg.c -o ffmpeg`. Copy compiled `ffmpeg`to `/opt/emby-server/bin`.

Note that you can change 1664000 to any value like 640k.
