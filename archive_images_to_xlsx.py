import pandas as pd
import os

rootdir = 'D:\\kepek'
generate_links = True

files = [(dpath, f) for dpath, _, files in os.walk(rootdir) for f in files if f.lower().endswith('.jpg') or f.lower().endswith('.jpeg') or f.lower().endswith('.gif') or f.lower().endswith('.png') or f.lower().endswith('.raw') or f.lower().endswith('.tiff') or f.lower().endswith('.psd') or f.lower().endswith('.dng') or f.lower().endswith('.bmp') or f.lower().endswith('.xcf') or f.lower().endswith('.cdr') or f.lower().endswith('.ai') or f.lower().endswith('.eps')]
if generate_links:
    files = [(dpath, '=HYPERLINK("{}", "{}")'.format(os.path.join(dpath, f), f)) for dpath, f in files]
df = pd.DataFrame(files, columns=['könyvtár', 'fájlnév'])
df = df.assign(sorszám=range(1, df.shape[0] + 1))
df = df.assign(**{'könyvtáron belüli sorszám': (None)})
for d in set(df['könyvtár']):
    idx = df.index[df['könyvtár'] == d]
    df.loc[idx, 'könyvtáron belüli sorszám'] = range(1, len(idx) + 1)
    df.loc[idx[1:], 'könyvtár'] = ''
df = df[['sorszám', 'könyvtáron belüli sorszám', 'könyvtár', 'fájlnév']]

writer = pd.ExcelWriter('kepek.xlsx', engine='xlsxwriter')
df.to_excel(writer, sheet_name='képek adatai', index=False)
worksheet = writer.sheets['képek adatai']
for idx, col in enumerate(df):
    if generate_links and col == 'fájlnév':
        max_len = max((df[col].astype(str).map(lambda x: x.split('", "')[-1][:-2]).map(len).max(), len(str(df[col].name)))) + 1
    else:
        max_len = max((df[col].astype(str).map(len).max(), len(str(df[col].name)))) + 1
    worksheet.set_column(idx, idx, max_len)
writer.save()
