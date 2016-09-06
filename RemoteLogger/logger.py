import requests

from time import sleep
import json
import sys


def main():
    answers=[]
    while True:
        requrl='http://93.50.192.43/orsetti/api.php'
        req=requests.get(requrl)
        rj=req.json()
        answers.append(rj)
        print '*',
        sys.stdout.flush()
        sleep(60)
        if len(answers)%1==0:
            print '\nSaving... (%i)' % len(answers),
            json.dump(answers,open('log.json','w'))
            print 'Done'

if __name__=='__main__':
    main()
