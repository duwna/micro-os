import java.io.*

//kotlinc builderFont.kt -include-runtime -d builderFont.jar
//java -jar builderFont.jar

lateinit var path: String

fun main(args: Array<String>) {
    path = args[0]
    File("$path\\a.exe").delete()
    runCommand("gcc -masm=intel -nostdlib $path\\main.c -o $path\\a.exe")
    println("gcc")
    runCommand("objcopy $path\\a.exe -O binary")
    println("objcopy")
    runCommand("nasm -f bin $path\\boot.asm -o $path\\boot.bin")
    println("nasm")
    createDisk()
    println("createDisk")
    runCommand("qemu-system-i386 $path\\disk.img")
    println("qemu")
}

fun runCommand(command: String) {
    val p = Runtime.getRuntime().exec(command)
    p.waitFor()
    p.destroy()
}

fun createDisk() {

    val bootFile = FileInputStream("$path\\boot.bin")
    val mainFile = FileInputStream("$path\\a.exe")
	val fontFile = FileInputStream("$path\\myfont.bin")
    val diskFile = FileOutputStream("$path\\disk.img")

    val bootBytes = ByteArray(510)
    bootFile.read(bootBytes, 0, bootBytes.size)

    val mainBytes = ByteArray(7168)
    mainFile.read(mainBytes, 0, mainBytes.size)

	val fontBytes = ByteArray(fontFile.available())
	fontFile.read(fontBytes, 0, fontBytes.size)

    with(diskFile) {
        write(bootBytes)
        write(byteArrayOf(0x55.toByte(), 0xaa.toByte()))
        write(mainBytes)
		write(fontBytes)
        close()
    }
}
