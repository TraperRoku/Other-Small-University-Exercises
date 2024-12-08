#!/bin/bash
#FILIP KAZMIERCZAK
#kf53844@zut.edu.pl
# SO IS1 224A LAB07

A=$1
case "$A" in
    -l)
        for module in /sys/module/*/; 
        do
            if [ -e "$module/refcnt" ]; 
            then
                name=$(basename "$module")
                licznik=$(cat "$module/refcnt")
                if [ -e "$module/holders" ]; 
                then
                    users=$(ls "$module/holders/" | tr '\n' ',')
                else
                    users=""
                fi
                echo "$name $licznik $users"
            fi
        done | sort
        ;;
    -b)
        for module in $(ls /sys/module); 
        do
            parameters="/sys/module/$module/parameters"

            [ -d "$parameters" ] && echo -n "$module " && ls "$parameters" | tr '\n' ',' | sort
        done 
        ;;
    *)
        echo "ERROR"
        exit 1
        ;;
esac

