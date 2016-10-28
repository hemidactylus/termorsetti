#!/usr/bin/env python

import requests

from time import sleep
import json
import sys
from datetime import datetime

from mongo_settings import gimme_db
# it is expected that gimme_db returns a PyMongo database object. Implement it your way, with your auth and so on.

collectionName='orsetti-readings'

dateFormat='%d %b %Y %H:%M:%S'

FieldConverters={
        'date': lambda d: datetime.strptime(d,dateFormat),
        'temp_int': float,
        'temp_int_dig' : float,
        'temp_ext': float,
        'heatindex': float,
        'humidity': float,
        'wetfloor': float,
    }

def main():
    loggerCollection=gimme_db(verbose=False)[collectionName]
    requrl='http://93.50.192.43/orsetti/api.php'
    req=requests.get(requrl)
    Resp=req.json()
    parsedResp={fld: conv(Resp[fld]) for fld,conv in FieldConverters.iteritems()}                
    loggerCollection.insert_one(parsedResp)

if __name__=='__main__':
    main()
