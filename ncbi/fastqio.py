#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun May 28 09:58:09 2017

@author: tom
"""

from Bio import SeqIO
for record in SeqIO.parse("./SRR3503015.fastq", "fastq"):
    print("%s, %s"%(record.id, record.seq))