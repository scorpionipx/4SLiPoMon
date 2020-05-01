from logging import getLogger

from serial import Serial, STOPBITS_TWO

from time import sleep


from lipo_4s_mon import APP_SLUG

LOGGER = getLogger(APP_SLUG)


class COMInterface:
    """

    """
    def __init__(self):
        """

        """
        self.com_port = None
        self.connected = False
        self.__connection__ = None

    def connect(self, com_port, baud_rate=57600):
        """connect

        :param com_port: COM port number
        :type com_port: int
        :param baud_rate: communication baud rate (default 57600)
        :type baud_rate: int
        :return: connection result
        :rtype: bool
        """
        if self.connected:
            LOGGER.warning('Already connected!')
            return False

        LOGGER.info('Connecting to 4S LiPo Monitor Driver Board...')
        try:
            self.__connection__ = Serial('COM{}'.format(com_port), baud_rate, stopbits=STOPBITS_TWO)
            self.connected = True
            sleep(2)
            LOGGER.info('Connected!')
            return True
        except Exception as exception:
            error = 'Connection failed! {}'.format(exception)
            LOGGER.error(error)
            return False

    def send_data(self, data):
        """send_data

        :param data: data to be sent
        :type data: int
        :return: number of bytes sent
        :rtype: int
        """
        bytes_sent = self.__connection__.write(bytes([data]))
        return bytes_sent

    def receive_data(self, nob=1, timeout=0.5):
        """receive_data

        :param nob: number of bytes expected
        :type nob: int
        :param timeout: read timeout in seconds
        :type timeout: float
        :return: received data
        :rtype: bytes
        """
        counter = 0
        refresh_rate = 0.01

        while self.__connection__.in_waiting < nob:
            counter += refresh_rate
            if counter > timeout:
                LOGGER.error('Read data timeout of {} seconds exceeded!'.format(timeout))
                return False
            sleep(refresh_rate)
        received = self.__connection__.read(nob)
        return received


if __name__ == '__main__':
    com = COMInterface()
    com.connect(
        com_port=4,
        baud_rate=57600,
    )
    sleep(2)
    com.send_data(10)
    # sleep(2)
    data = com.receive_data(35)
    for d in data:
        print(d)
