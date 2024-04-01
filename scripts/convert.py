import math

raw = [
    """.id = 0,
    .name = "base",

    .min_steps = -7425,
    .max_steps = 6250,
    .ref_steps = -7425,
    
    .goto_after_calibrate = 0,

    .motor_steps_per_rev = 400,
    .enc_ticks_per_rev = 3840, // max 3000 RPM, DIP switches 1100

    .motor_reduction = 40.0,
    .enc_reduction = 40.0,

    .direction = -1,

    .max_speed = 80.0,
    .max_accel = 240.0,
    .calibration_speed = -10.0,

    .step_pin = 0,
    .dir_pin = 1,
    .enc_a_pin = 14,
    .enc_b_pin = 15,

    .speed_filter_strength = 5.0,

    .lim_pin = 26,""",
    """.id = 1,
    .name = "shoulder",

    .min_steps = -2350,
    .max_steps = 4000,
    .ref_steps = -2450,
    
    .goto_after_calibrate = -1750,

    .motor_steps_per_rev = 400,
    .enc_ticks_per_rev = 960, // max 3000 RPM, DIP switches 1100

    .motor_reduction = 50.0,
    .enc_reduction = 50.0,

    .direction = 1,

    .max_speed = 60.0,
    .max_accel = 240.0,
    .calibration_speed = -5.0,

    .step_pin = 2,
    .dir_pin = 3,
    .enc_a_pin = 16,
    .enc_b_pin = 17,

    .speed_filter_strength = 5.0,

    .lim_pin = 27,""",
    """.id = 2,
    .name = "elbow",

    .min_steps = -8000,
    .max_steps = 8100,
    .ref_steps = 8100,
    
    .goto_after_calibrate = 3500,

    .motor_steps_per_rev = 400,
    .enc_ticks_per_rev = 3840, // max 3000 RPM, DIP switches 1100

    .motor_reduction = 50.0,
    .enc_reduction = 50.0,

    .direction = 1,

    .max_speed = 160.0,
    .max_accel = 220.0,
    .calibration_speed = 5.0,

    .step_pin = 4,
    .dir_pin = 5,
    .enc_a_pin = 18,
    .enc_b_pin = 19,

    .speed_filter_strength = 5.0,

    .lim_pin = 28,""",
    """.id = 3,
    .name = "forearm roll",

    .min_steps = -4250,
    .max_steps = 7046,
    .ref_steps = 7046,
    
    .goto_after_calibrate = 0,

    .motor_steps_per_rev = 400,
    .enc_ticks_per_rev = 960, // max 3000 RPM, DIP switches 1100

    .motor_reduction = 39.2,
    .enc_reduction = 39.2,

    .direction = -1,

    .max_speed = 240.0,
    .max_accel = 1200.0,
    .calibration_speed = 10.0,

    .step_pin = 6,
    .dir_pin = 7,
    .enc_a_pin = 20,
    .enc_b_pin = 21,

    .speed_filter_strength = 5.0,

    .lim_pin = 29,""",
    """.id = 4,
    .name = "wrist pitch",

    .min_steps = -1750,
    .max_steps = 2250,
    .ref_steps = -1750,
    
    .goto_after_calibrate = 0,

    .motor_steps_per_rev = 800,
    .enc_ticks_per_rev = 2000, // max 3000 RPM, DIP switches 0100

    .motor_reduction = 9.1455,
    .enc_reduction = 9.1455,

    .direction = 1,

    .max_speed = 200.0,
    .max_accel = 600.0,
    .calibration_speed = -10.0,

    .step_pin = 8,
    .dir_pin = 9,
    .enc_a_pin = 22,
    .enc_b_pin = 23,

    .speed_filter_strength = 5.0,

    .lim_pin = 30,""",
    """.id = 5,
    .name = "wrist roll",

    .min_steps = -3000,
    .max_steps = 3250,
    .ref_steps = 3250,
    
    .goto_after_calibrate = 0,

    .motor_steps_per_rev = 400,
    .enc_ticks_per_rev = 640, // max 6000 RPM, DIP switches 0011

    .motor_reduction = 19.0,
    .enc_reduction = 19.0,

    .direction = 1,

    .max_speed = 1500.0,
    .max_accel = 8000.0,
    .calibration_speed = 10.0,

    .step_pin = 10,
    .dir_pin = 11,
    .enc_a_pin = 24,
    .enc_b_pin = 25,

    .speed_filter_strength = 5.0,

    .lim_pin = 31,"""
]


def extract(entry):
    # Extract id, name, min_steps, max_steps, motor_steps_per_rev, motor_reduction, direction,
    # max_speed, max_accel entry and return them as a dictionary

    return {
        "id": int(entry.split(".id = ")[1].split(",")[0]),
        "name": entry.split(".name = ")[1].split(",")[0].strip('"'),
        "min_steps": int(entry.split(".min_steps = ")[1].split(",")[0]),
        "max_steps": int(entry.split(".max_steps = ")[1].split(",")[0]),
        "motor_steps_per_rev": int(entry.split(".motor_steps_per_rev = ")[1].split(",")[0]),
        "motor_reduction": float(entry.split(".motor_reduction = ")[1].split(",")[0]),
        "direction": int(entry.split(".direction = ")[1].split(",")[0]),
        "max_speed": float(entry.split(".max_speed = ")[1].split(",")[0]),
        "max_accel": float(entry.split(".max_accel = ")[1].split(",")[0]),
    }

def process(entry):
    # Solve for min and max degrees
    min_deg = entry["min_steps"] / entry["motor_steps_per_rev"] / entry["motor_reduction"] * 360
    max_deg = entry["max_steps"] / entry["motor_steps_per_rev"] / entry["motor_reduction"] * 360
    if entry["direction"] == -1:
        min_deg, max_deg = -max_deg, -min_deg
    return (min_deg, max_deg)

for entry in raw:
    extracted = extract(entry)
    (min_deg, max_deg) = process(extracted)
    max_speed_rad = math.radians(extracted["max_speed"] - 2)
    max_accel_rad = math.radians(extracted["max_accel"])
    print(f"{extracted['name']} ({extracted['id']}):\n" + 
    "  Min degrees: {:.4f} deg\n".format(min_deg) +
    "  Max degrees: {:.4f} deg\n".format(max_deg) +
    "  Max speed: {:.4f} deg/sec\n".format(extracted["max_speed"]) +
    "  Max speed: {:.4f} rad/sec\n".format(max_speed_rad) +
    "  Max acceleration: {:.4f} deg/sec^2\n".format(extracted["max_accel"]) +
    "  Max acceleration: {:.4f} rad/sec^2\n".format(max_accel_rad))