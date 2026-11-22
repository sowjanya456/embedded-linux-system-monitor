SUMMARY = "Embedded Linux System Monitoring Application"
DESCRIPTION = "Monitors CPU statistics from /proc/stat"
LICENSE = "CLOSED"

SRC_URI = "file://system-monitor.c"

S = "${WORKDIR}"

do_compile() {
    ${CC} ${CFLAGS} ${LDFLAGS} system-monitor.c -o system-monitor
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 system-monitor ${D}${bindir}/system-monitor
}