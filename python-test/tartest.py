import os.path
import tarfile
import zipfile

import rarfile

"""
Python program to extract tar or tar.gz files having 
specified file extensions only
"""

ext = ['.txt', '.doc', '.docx', '.pdf', '.xml']
fname = 'mycroft.rar'

if (fname.endswith('tar.gz')):
    tar = tarfile.open(fname, 'r:gz')
    for member in tar.getmembers():
        if os.path.splitext(member.name)[1] in ext:
            tar.extract(member, path='gz')
    tar.close()
elif (fname.endswith('tar')):
    tar_gz = tarfile.open(fname, 'r')
    for member in tar_gz.getmembers():
        if os.path.splitext(member.name)[1] in ext:
            tar_gz.extract(member, path='tar')
    tar_gz.close()
elif (fname.endswith('zip')):
    zip_file = zipfile.ZipFile(fname, 'r')
    for member in zip_file.namelist():
        if os.path.splitext(member)[1] in ext:
            zip_file.extract(member, path='zip')
elif (fname.endswith('rar')):
    rar_file = rarfile.RarFile(fname)
    for member in rar_file.namelist():
        if os.path.splitext(member)[1] in ext:
            rar_file.extract(member, path='rar')