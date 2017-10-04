#!/usr/bin/python
# -*- coding: utf-8 -*-

import glob
import os
import os.path
import shutil
import sys
import tarfile
import zipfile
from subprocess import Popen, PIPE, call

import rarfile

# Get all keywords to be found
f = open('/home/vikram/Downloads/keys.txt', 'r')
keys = set(f.read().split())

# Get filename, path, source ip and destination ip from arguments
filename = sys.argv[1]
filepath = sys.argv[2]
srcip = sys.argv[3]
dstip = sys.argv[4]

fname = os.path.basename(filepath)
fext = os.path.splitext(filepath)[1]
#filename = sys.argv[1]
# print filename, fname, fext

# Global variables
plaintext_extensions = ['.txt', '.doc', '.html', 'htm', 'rtf', 'xml', 'xls', 'json']
FNULL = open(os.devnull, 'w')


def notice_printer(filename):
    with open('/home/vikram/PycharmProjects/C-Basics/KeywordMatching/somefile.txt', 'a') as the_file:
        the_file.write(
            '{"id.orig_h":"%s","id.orig_p":"%s","id.resp_h":"%s","id.resp_p":"%s",'
            '"msg":"Keyword matched in file %s having path %s","note":"KeywordMatch::Matched"}'
            % (sys.argv[3], sys.argv[4], sys.argv[5], sys.argv[6], filename, filepath))
    return


def extension_pdf(filename):
    for key in keys:
        call(['pdftotext', '%s' % filename])
        new_fn = os.path.splitext(filename)
        new_fn = new_fn[0] + '.txt'
        pdf_res = call(['grep', '-ic', '%s' % key, '%s' % new_fn], stdout=FNULL)
        if pdf_res == 0:
            notice_printer(filename)
            break


def extension_docx(filename):
    docxread = Popen(['docx2txt', '%s' % filename], stdout=PIPE).communicate()[0]
    for key in keys:
        if key in docxread:
            notice_printer(filename)
            break


def extension_txt(filename):
    for key in keys:
        txt_result = call(['grep', '-ic', '%s' % key, '%s' % filename], stdout=FNULL)
        if txt_result == 0:
            notice_printer(filename)
            break


def extension_tar(filename):
    tar = tarfile.open(filename)
    tar_gz = tarfile.open(fname, 'r')
    for member in tar_gz.getmembers():
        if os.path.splitext(member.name)[1] in plaintext_extensions:
            tar_gz.extract(member, path='tar')
    tar.close()
    ext_tar = glob.glob("tar/*")
    for files in ext_tar:
        fn_tar = os.path.basename(files)
        fext_tar = os.path.splitext(files)[1]
        os.chdir('tar')
        if fext_tar.lower() == '.pdf':
            extension_pdf(fn_tar)
        if fext_tar.lower() == '.docx':
            extension_docx(fn_tar)
        if fext_tar.lower() in plaintext_extensions:
            extension_txt(fn_tar)
        os.chdir('..')
    shutil.rmtree('tar')


def extension_targz(filename):
    tar = tarfile.open(filename, 'r:gz')
    for member in tar.getmembers():
        if os.path.splitext(member.name)[1] in plaintext_extensions:
            tar.extract(member, path='gz')
    tar.close()
    ext_tar = glob.glob("gz/*")
    for files in ext_tar:
        fn_tar = os.path.basename(files)
        fext_tar = os.path.splitext(files)[1]
        os.chdir('gz')
        if fext_tar.lower() == '.pdf':
            extension_pdf(fn_tar)
        if fext_tar.lower() == '.docx':
            extension_docx(fn_tar)
        if fext_tar.lower() in plaintext_extensions:
            extension_txt(fn_tar)
        os.chdir('..')
    shutil.rmtree('gz')


def extension_zip(filename):
    zip_file = zipfile.ZipFile(filename, 'r')
    for member in zip_file.namelist():
        if os.path.splitext(member)[1] in plaintext_extensions:
            zip_file.extract(member, path='zip')
    ext_zip = glob.glob("zip/*")
    for files in ext_zip:
        fn_zip = os.path.basename(files)
        fext_zip = os.path.splitext(files)[1]
        os.chdir('zip')
        if fext_zip.lower() == '.pdf':
            extension_pdf(fn_zip)
        if fext_zip.lower() == '.docx':
            extension_docx(fn_zip)
        if fext_zip.lower() in plaintext_extensions:
            extension_txt(fn_zip)
        os.chdir('..')
    shutil.rmtree('zip')
    return


def extension_rar(filename):
    rar_file = rarfile.RarFile(filename)
    for member in rar_file.namelist():
        if os.path.splitext(member)[1] in plaintext_extensions:
            rar_file.extract(member, path='rar')
    ext_rar = glob.glob("rar/*")
    for files in ext_rar:
        fn_rar = os.path.basename(files)
        fext_rar = os.path.splitext(files)[1]
        os.chdir('rar')
        if fext_rar.lower() == '.pdf':
            extension_pdf(fn_rar)
        if fext_rar.lower() == '.docx':
            extension_docx(fn_rar)
        if fext_rar.lower() in plaintext_extensions:
            extension_txt(fn_rar)
        os.chdir('..')
    shutil.rmtree('rar')
    return


os.chdir('extract_files')
if fext.lower() == '.pdf':
    extension_pdf(filename)
elif fext.lower() == '.docx':
    extension_docx(filename)
elif fname.endswith('tar.gz'):
    extension_targz(filename)
elif fext.lower() == '.tar':
    extension_tar(filename)
elif fname.endswith('zip'):
    extension_zip(filename)
elif fname.endswith('rar'):
    extension_rar(filename)
elif fext.lower() in plaintext_extensions:
    extension_txt(filename)
os.chdir('..')
