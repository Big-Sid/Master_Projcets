#!/bin/sh
curl -L https://bit.ly/2ATet9V -s|sed '1d' |cut -d, -f2-| sed 's/,/ /1' | sed 's/,/, /1' | sed 's/\@.*/@****.***/'
