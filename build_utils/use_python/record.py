from datetime import datetime


def log_message(message: str) -> None:
    """
    Formats a message with the current date and time, then prints it.

    Parameters:
        message (str): The message to be printed.

    Returns:
        None
    """
    current_time = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    print(f"[{current_time}] {message}")
