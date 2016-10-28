#!/usr/bin/env python


from datetime import datetime, timedelta
import pandas as pd
import matplotlib.pyplot as plt
import sys

from mongo_settings import gimme_db
# it is expected that gimme_db returns a PyMongo database object. Implement it your way, with your auth and so on.

collectionName='orsetti-readings'

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
            {
                'wetfloor': 'Wet Floor',
            },
        ]
HASLEGEND=[True,True,True]
PLOTTITLE=['Temperature (^C)','Rel. Humidity (%%)','Wet Floor']

def main(daysBack=2):
    # loading data from DB
    loggerCollection=gimme_db(verbose=False)[collectionName]

    _qry={'date':{'$gte': datetime.now()-timedelta(days=daysBack)}}
    _prj={'_id':False}

    df=pd.DataFrame(list(loggerCollection.find(_qry,_prj)))
    df=df.set_index('date')
    
    # plotting
    axTemp = plt.subplot2grid((2,2), (0,0), colspan=2)
    axHum = plt.subplot2grid((2,2), (1, 0))
    axWet = plt.subplot2grid((2,2), (1, 1))
    ax=[axTemp,axHum,axWet]
    
    for fax,flist,xlegend,ylabel in zip(ax,FIELDS,HASLEGEND,PLOTTITLE):
        for fname,flabel in flist.iteritems():
            df[fname].plot(style='o',label=flabel,ax=fax)
        fax.legend()
        fax.get_xaxis().set_visible(xlegend)
        fax.set_ylabel(ylabel)
    plt.show()

if __name__=='__main__':
    _help='''
        Usage: ./orsettiplotter.py [-t NUMDAYS]
    '''
    
    showHelp=False
    daysBack=2
    
    if len(sys.argv)>1:
        alist=sys.argv[1:]
        while alist:
            qarg=alist.pop(0)
            if qarg=='-t':
                if alist:
                    daysBack=float(alist.pop(0))
                else:
                    showHelp=True
            else:
                print 'Unrecognised command line argument: %s' % qarg

    if showHelp:
        print _help
    else:
        main(daysBack)
