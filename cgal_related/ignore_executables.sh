for f in $(find . -perm /111 -type f | grep -v '.git' | sed 's#^./##' | sort -u); do grep -q "$f" .gitignore || echo "$f" >> .gitignore ; done
