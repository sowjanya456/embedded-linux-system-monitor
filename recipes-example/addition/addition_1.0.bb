SUMMARY = "Addition program with runtime input"
LICENSE = "CLOSED"

SRC_URI = "file://addition.c"

S = "${WORKDIR}"

do_compile() {
    ${CC} ${CFLAGS} ${LDFLAGS} addition.c -o addition
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 addition ${D}${bindir}/addition
}