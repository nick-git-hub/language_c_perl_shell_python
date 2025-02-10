#include <stdio.h>
#include <string.h>                               
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>

int main(void)
{
    int hourOffset = 2;
    char zoneFilename[512];
    char localtimeLink[256];
    bool bLink = false;

    const char etcLocaltimeFilename[] = "/etc/localtime";
    const char tmpLocaltimeFilename[] = "/tmp/localtime";
    const char zoneRootDir[] = "/usr/share/zoneinfo";
    const char etcDirFormat[] = "%s/Etc/GMT";
    const char rootDirFormat [] = "%s/GMT";
    const char *format;
    char cmDefaultZoneFilenameFormat[256];
    int cmDefaultZoneFilenameFormatLen;
    int readlinkLen;

    /* Check if ~/Etc directory existed, OpenWRT install these ~/Etc/xxx zone files at the zoneinfo root instead */
    char path[256];
    snprintf(path, sizeof(path), "%s/Etc", zoneRootDir);
    format = etcDirFormat;
    /* cmDefaultZoneFilenameFormat is either "/usr/share/zoneinfo/GMT" or "/usr/share/zoneinfo/Etc/GMT"  */
    cmDefaultZoneFilenameFormatLen = snprintf(cmDefaultZoneFilenameFormat, sizeof(cmDefaultZoneFilenameFormat), format, zoneRootDir);

    /* /etc/localtime maybe on a read-only mount, and it may symlink to /var/localtime or /tmp/localtime,
     * set up a symlink to wanted zone file */
    readlinkLen = readlink(etcLocaltimeFilename, localtimeLink, sizeof(localtimeLink)-1);
    printf("localtimeLink:%s\n",localtimeLink);
    printf("etcLocaltimeFilename:%s, len%d\n",etcLocaltimeFilename,readlinkLen);

    if (readlinkLen >= 0)
    {
        localtimeLink[readlinkLen] = '\0';
    }
    else if (errno == ENOENT)
    {
        /* no symlink and /etc/localtime does not exist, create symlink to /tmp/localtime */
        memcpy(localtimeLink, tmpLocaltimeFilename, sizeof(tmpLocaltimeFilename));
        symlink(localtimeLink, etcLocaltimeFilename);
    }

    /* coverity[fs_check_call] - avoid TOCTOU with unlink() */
    readlinkLen = readlink(localtimeLink, zoneFilename, sizeof(zoneFilename)-1);
    printf("zoneFilename:%s\n",zoneFilename);
    printf("localtimeLink:%s, len%d\n",localtimeLink,readlinkLen);

    if (readlinkLen >= 0)
    {
        zoneFilename[readlinkLen] = '\0';
        printf("cmDefaultZoneFilenameFormat:%s\n",cmDefaultZoneFilenameFormat);
        /* There is a symlink.
         * Check if this is a ~GMTXXX link that is populated by previous CM UTC offset, we will unlink and re-add a new symlin
         * Existing symlink to a location zone file (by the user) is not updated by the CM UTC offset */
        if (strncmp(zoneFilename, cmDefaultZoneFilenameFormat, cmDefaultZoneFilenameFormatLen) == 0)
        {
            if (unlink(localtimeLink) == -1)
            {
                printf("failed to unlink %s - errno %d!", localtimeLink, errno);
            }
            bLink = true;
        }
    }
    else if (errno == ENOENT)
    {
        /* No symlink to any zone file, add a symlink. */
        bLink = true;
    }
    else 
    {
        printf("Error occurred, errno = %d\n", errno);
    }
    printf("bLine=%d\n",bLink);

    if (bLink)
    {

        /* Add link to zone file in ~GMTXXX, as this comes from CM UTC offset */
        snprintf(zoneFilename, sizeof(zoneFilename), "%s%+d", cmDefaultZoneFilenameFormat, -hourOffset);
        symlink(zoneFilename, localtimeLink);
    }

    const char *target = "test";
    const char *linkname = "test2";
    if(unlink("test2")== -1)
    {
    	printf("unlink error");
    }

    if (symlink(target, linkname) == -1) {
        perror("symlink failed");
        return 1;
    }

    return 0;
}
