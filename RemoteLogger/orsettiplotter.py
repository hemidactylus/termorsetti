#!/usr/bin/env python


from datetime import datetime, timedelta
import pandas as pd
import matplotlib.pyplot as plt

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
        ]

def main(daysBack=2):
    # loading data from DB
    loggerCollection=gimme_db(verbose=False)[collectionName]

    _qry={'date':{'$gte': datetime.now()-timedelta(days=daysBack)}}
    _prj={'_id':False}

    df=pd.DataFrame(list(loggerCollection.find(_qry,_prj)))
    df=df.set_index('date')
    
    # plotting
    fig,ax=plt.subplots(len(FIELDS),1)
    for fax,flist,xlegend,ylabel in zip(ax,FIELDS,[True,True],['Temperature (^C)','Rel. Humidity (%%)']):
        for fname,flabel in flist.iteritems():
            df[fname].plot(style='o',label=flabel,ax=fax)
        fax.legend()
        fax.get_xaxis().set_visible(xlegend)
        fax.set_ylabel(ylabel)
    plt.show()

if __name__=='__main__':
    main()
