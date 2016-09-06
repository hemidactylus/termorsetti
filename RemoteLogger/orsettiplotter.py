#!/usr/bin/env python

import matplotlib.pyplot as plt
import pandas as pd
import json

FNAME='log.json'

FIELDS=[
            {
                'heatindex': 'Heat Index',
                'temp_ext': 'External Temp',
                'temp_int': 'Internal Temp',
                'temp_int_dig': 'Internal Temp (Dig)',
            },
            {
                'humidity': 'Relative Humidity',
            },
        ]

def main():
    # loading
    data=json.load(open(FNAME))
    df=pd.DataFrame(data)
    df=df.set_index('date')
    
    # plotting
    fig,ax=plt.subplots(len(FIELDS),1)
    for fax,flist in zip(ax,FIELDS):
        for fname,flabel in flist.iteritems():
            df[fname].plot(label=flabel,ax=fax)
        fax.legend()
    plt.show()

if __name__=='__main__':
    main()
