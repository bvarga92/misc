import os
import glob
from pymediainfo import MediaInfo
import pandas as pd
import shutil


directory = '.'
recursive = False
truncate_to_sec = False
move_files = True


videos = []
if recursive:
    videos += [{'file': v} for v in glob.glob(os.path.join(directory, '**/*.mp4'), recursive=True)]
    videos += [{'file': v} for v in glob.glob(os.path.join(directory, '**/*.m4v'), recursive=True)]
    videos += [{'file': v} for v in glob.glob(os.path.join(directory, '**/*.avi'), recursive=True)]
    videos += [{'file': v} for v in glob.glob(os.path.join(directory, '**/*.mkv'), recursive=True)]
    videos += [{'file': v} for v in glob.glob(os.path.join(directory, '**/*.wmv'), recursive=True)]
    videos += [{'file': v} for v in glob.glob(os.path.join(directory, '**/*.flv'), recursive=True)]
else:
    videos += [{'file': v} for v in glob.glob(os.path.join(directory, '*.mp4'))]
    videos += [{'file': v} for v in glob.glob(os.path.join(directory, '*.m4v'))]
    videos += [{'file': v} for v in glob.glob(os.path.join(directory, '*.avi'))]
    videos += [{'file': v} for v in glob.glob(os.path.join(directory, '*.mkv'))]
    videos += [{'file': v} for v in glob.glob(os.path.join(directory, '*.wmv'))]
    videos += [{'file': v} for v in glob.glob(os.path.join(directory, '*.flv'))]

for v in videos:
    try:
        duration = [int(track.to_data()['duration']) for track in MediaInfo.parse(v['file']).tracks if track.track_type == 'Video']
    except:
        v['duration'] = -1
        continue
    if len(duration) == 1:
        duration = duration[0]
        if truncate_to_sec:
            duration //= 1000
    else:
        v['duration'] = -1
        continue
    v['duration'] = duration
videos.sort(key=lambda d: d['duration'])
videos = pd.DataFrame(videos)

same_duration = []
duration_prev = None
for v in videos.iterrows():
    duration = v[1]['duration']
    if duration < 0:
        continue
    if duration == duration_prev:
        continue
    temp = videos[videos['duration'] == duration]
    if temp.shape[0] > 1:
        same_duration.append({'duration': duration, 'files': list(temp['file'])})
        duration_prev = duration

if len(same_duration) > 0:
    if move_files:
        for sd in same_duration:
            dstdir = os.path.join(directory, 'same_duration', str(sd['duration']))
            if not os.path.exists(dstdir):
                os.makedirs(dstdir)
            for file in sd['files']:
                shutil.move(file, dstdir)
    else:
        pd.DataFrame(same_duration).to_csv('same_duration.txt', index=False, sep='\t')
else:
    print('No videos with equal durations found.')